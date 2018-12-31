﻿//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Corona Labs Inc.
// Contact: support@coronalabs.com
//
// This file is part of the Corona game engine.
//
// Commercial License Usage
// Licensees holding valid commercial Corona licenses may use this file in
// accordance with the commercial license agreement between you and 
// Corona Labs Inc. For licensing terms and conditions please contact
// support@coronalabs.com or visit https://coronalabs.com/com-license
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of the GNU General
// Public license version 3. The license is as published by the Free Software
// Foundation and appearing in the file LICENSE.GPL3 included in the packaging
// of this file. Please review the following information to ensure the GNU 
// General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html
//
// For overview and more information on licensing please refer to README.md
//
//////////////////////////////////////////////////////////////////////////////

'use strict';

var videoLibrary =
{
	//
	// ImageProvider
	//

	jsImageProviderCreate: function (thiz, w, h) {
		if (navigator.mediaDevices) {
			var constraints = { video: true };
			var chunks = [];
			var jsVideoRecorderCallback = Module.cwrap('jsVideoRecorderCallback', 'null', ['number', 'number', 'number', 'number', 'number']);

			var promise = navigator.mediaDevices.getUserMedia(constraints);
			promise.then(
				function (stream) {
					// async

					var mediaRecorder = new MediaRecorder(stream);
					Module.appObjects.push(mediaRecorder);
					var objID = Module.appObjects.length;
					//console.log('JS objID', objID);

					var viewPort = canvas.getBoundingClientRect();
					var scale = viewPort.width / Module.appInitWidth;
					var video = document.createElement('video');
					video.id = Module.appElementCounter++;
					video.type = 'video';
					video.x = 0;
					video.y = 0;
					video.w = w;
					video.h = h;

					video.style.position = "absolute";
					video.style.left = (viewPort.left + video.x * scale) + 'px';
					video.style.top = (viewPort.top + video.y * scale) + 'px';
					video.style.width = video.w + 'px';
					video.style.height = video.h + 'px';

					video.src = window.URL.createObjectURL(stream);
					mediaRecorder.video = video;		// save

					var btn = document.createElement('button');
					btn.id = Module.appElementCounter++;
					btn.type = 'button';

					var bsize = 25;
					btn.x = video.w - bsize - 1;
					btn.y = 1;
					btn.w = bsize;
					btn.h = bsize;

					btn.style.position = "absolute";
					btn.style.left = (viewPort.left + btn.x * scale) + 'px';
					btn.style.top = (viewPort.top + btn.y * scale) + 'px';
					btn.style.width = btn.w + 'px';
					btn.style.height = btn.h + 'px';
					btn.style.backgroundColor = "yellow";
					btn.onclick = function () {
						// capture frame
						var mycanvas = document.createElement('canvas');
						mycanvas.height = video.videoHeight;
						mycanvas.width = video.videoWidth;
						var ctx = mycanvas.getContext('2d');
						ctx.drawImage(video, 0, 0, mycanvas.width, mycanvas.height);

						// get rgba
						var img = ctx.getImageData(0, 0, mycanvas.width, mycanvas.height);
						if (img && img.width > 0 && img.height > 0) {
							var size = img.width * img.height * 4;

							var body = new Uint8Array(img.data);
							body_buffer = Module._malloc(body.length);
							body_length = body.length;
							Module.writeArrayToMemory(body, body_buffer);

							//console.log('captue', img, body);
							jsVideoRecorderCallback(thiz, 5, img.width, img.height, body_buffer);			// onDataAvailable

							Module._free(body_buffer);
						}

						mycanvas.remove();
					};
					mediaRecorder.btn = btn;		// save

					//console.log('media recorder created');
					jsVideoRecorderCallback(thiz, 7, objID, 0, 0);			// 7 ==> 'onCreated'
				})
				.catch(
				function (err) {
					// async
					Module.printErr('Error: Failed to start media recorder\n', err.name);
					//jsVideoRecorderCallback(thiz, 1, 0, 0, 0);			// 1 ==> 'onerror'
				});
		}
		else {
			Module.printErr('Error: MediaRecorder requires getUserMedia supported');
		}
	},

	jsDeleteObject: function (id) {
		if (id > 0 && Module.hasOwnProperty(id))
		{
			Module.appObjects[id - 1] = null;
		}
	},

	jsImageProviderShow: function (id) {
		var mr = Module.appObjects[id - 1];		// mediarecorder
		//console.log('Show', $0, mr, mr.video);
		if (mr && mr.video) {
			var vid = mr.video;
			var btn = mr.btn;

			canvas.parentNode.appendChild(vid);
			canvas.parentNode.appendChild(btn);

			vid.controls = false;
			vid.play();
			return true;
		}
		return false;
	},

	jsImageProviderHide: function (id) {
		var mr = Module.appObjects[id - 1];		// mediarecorder
		//console.log(mr, mr.video);
		if (mr && mr.video) {
			mr.video.remove();
			mr.btn.remove();
		}
	},


	//
	// video
	//

	jsVideoInit: function (id, thiz) {
		var obj = document.getElementById(id);
		if (obj) {
			// unsafe
			obj.thiz = thiz;
			var jsVideoCallback = Module.cwrap('jsVideoCallback', 'null', ['number', 'number']);

			obj.onloadeddata = function () {
				// unsafe obj.thiz
				jsVideoCallback(obj.thiz, 1); // 1 ==>'ready'
			};

			obj.onended = function () {
				jsVideoCallback(obj.thiz, 2);			// 2 ==> 'ended'
			};
			return true;
		}
		return false;
	},

	jsVideoLoad: function(id, source, autoPlay)
	{
		var obj = document.getElementById(id);
		var url = UTF8ToString(source);
		if (obj)
		{
			obj.autoplay = autoPlay;
			obj.src = url;
		}
	},

	jsVideoPlay: function (id) {
		var obj = document.getElementById(id);
		if (obj) {
			obj.play();
		}
	},

	jsVideoPause: function(id)
	{
		var obj = document.getElementById(id);
		if (obj)
		{
			obj.pause();
		}
	},

	jsVideoCurrentTime: function (id) {
		var obj = document.getElementById(id);
		return obj ? obj.currentTime : 0;
	},

	jsVideoSeek: function(id, seekTo)
	{
		var obj = document.getElementById(id);
		if (obj && seekTo >= 0)
		{
			obj.currentTime = seekTo;
		}
	},

	jsVideoTotalTime: function (id) {
		var obj = document.getElementById(id);
		return obj ? obj.duration : 0;
	},

	jsVideoIsMuted: function (id) {
		var obj = document.getElementById(id);
		return obj ? obj.muted : true;
	},

	jsVideoMuted: function (id, val) {
		var obj = document.getElementById(id);
		if (obj) {
			obj.muted = val;
		}
	},

	//
	// audio recorder
	//

	jsAudioRecorderInit: function (thiz, file) {
		if (navigator.mediaDevices) {
			var fileName = UTF8ToString(file);
			var constraints = { audio: true };
			var chunks = [];
			var jsAudioRecorderCallback = Module.cwrap('jsAudioRecorderCallback', 'null', ['number', 'number', 'number', 'number']);

			var promise = navigator.mediaDevices.getUserMedia(constraints);
			promise.then(
				function (stream) {
					// async
					var mediaRecorder = new MediaRecorder(stream);
					Module.appObjects.push(mediaRecorder);
					var objID = Module.appObjects.length;

					mediaRecorder.ondataavailable = function (e) {
						chunks.push(e.data);
						jsAudioRecorderCallback(thiz, 5, 0, 0);			// 5 ==> 'ondataavailable'
					};

					mediaRecorder.onresume = function (e) {
						jsAudioRecorderCallback(thiz, 4, 0, 0);			// 4 ==> 'onresume'
					};

					mediaRecorder.onpause = function (e) {
						jsAudioRecorderCallback(thiz, 6, 0, 0);			// 6 ==> 'onpause'
					};

					mediaRecorder.onerror = function (e) {
						jsAudioRecorderCallback(thiz, 1, 0, 0);			// 1 ==> 'onerror'
					};

					mediaRecorder.onstart = function (e) {
						jsAudioRecorderCallback(thiz, 2, 0, 0);			// 2 ==> 'onstart'
					};

					mediaRecorder.onstop = function (e) {
						var blob = new Blob(chunks, { type: 'audio/ogg; codecs=opus' });
						chunks = [];

						var reader = new FileReader();
						reader.addEventListener("loadend", function () {
							var body = new Uint8Array(reader.result, 0, reader.result.byteLength);
							FS.writeFile(fileName, body, { encoding: 'binary' });
							jsAudioRecorderCallback(thiz, 3, 0, 0);			// 3 ==> 'onstop'
						});
						reader.readAsArrayBuffer(blob);
					};

					jsAudioRecorderCallback(thiz, 7, objID, 0);			// 7 ==> 'onCreated'
				})
				.catch(
				function (err) {
					// async
					console.log('Could not start media recorder', err.name);
					jsAudioRecorderCallback(thiz, 1, 0, 0);			// 1 ==> 'onerror'
				});
		}
		else {
			Module.printErr('Error: mediaRecorder requires getUserMedia supported');
		}
	},

	jsAudioRecorderStart: function (id, rate) {
		if (id > 0 && Module.hasOwnProperty(id)) {
			var r = Module.appObjects[$0 - 1];		// to index
			try { r.start(); }
			catch (e) { console.log(e); }
		}
	},

	jsAudioRecorderStop: function(id)
	{
		if (id > 0 && Module.hasOwnProperty(id)) {
			var r = Module.appObjects[$0 - 1];		// to index
			try { r.stop(); }
			catch (e) { console.log(e); }
		}
	},

	//
	// webview
	//

	jsWebViewOpen: function (id, _url) {
		var obj = document.getElementById(id);
		var url = UTF8ToString(_url);
		if (obj) {
			obj.src = url;
		}
	},

}

//autoAddDeps(videoLibrary, '$jsLanguage');
mergeInto(LibraryManager.library, videoLibrary);
