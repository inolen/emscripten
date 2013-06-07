
// === Auto-generated postamble setup entry stuff ===

function callMain(args) {
  assert(!preRunTasks.length, 'cannot call main when preRun functions remain to be called');

  args = args || Module['arguments'];

  var argc = args.length+1;
  function pad() {
    for (var i = 0; i < {{{ QUANTUM_SIZE }}}-1; i++) {
      argv.push(0);
    }
  }
  var argv = [allocate(intArrayFromString("/bin/this.program"), 'i8', ALLOC_NORMAL) ];
  pad();
  for (var i = 0; i < argc-1; i = i + 1) {
    argv.push(allocate(intArrayFromString(args[i]), 'i8', ALLOC_NORMAL));
    pad();
  }
  argv.push(0);
  argv = allocate(argv, 'i32', ALLOC_NORMAL);

#if BENCHMARK
  var start = Date.now();
#endif

  var ret;

  initialStackTop = STACKTOP;
  try {
    ret = Module['_main'](argc, argv, 0);
  }
  catch(e) {
    if (e.name == 'ExitStatus') {
      return e.status;
    } else if (e == 'SimulateInfiniteLoop') {
      Module['noExitRuntime'] = true;
    } else {
      throw e;
    }
  }

#if BENCHMARK
  Module.realPrint('main() took ' + (Date.now() - start) + ' milliseconds');
#endif

  return ret;
}

{{GLOBAL_VARS}}

function preload(onready) {
  preRun(function (err) {
    onready(err);
  });
}
Module['preload'] = Module.preload = preload;

function run(args) {
  if (!ABORT) {
    Module.printErr('module is already running');
    return 0;
  }
  ABORT = false;

  var _run = function () {
    preload(function (err) {
      if (err) throw err;
      if (ABORT) return;

      initRuntime();

      preMain();

      if (Module['_main']) {
        ret = callMain(args);
      }

      if (!Module['noExitRuntime']) {
        exit();
      }
    });
  };

  if (Module['setStatus']) {
    Module['setStatus']('Running...');
    setTimeout(function() {
      setTimeout(function() {
        Module['setStatus']('');
      }, 1);
      _run(args);
    }, 1);
  } else {
    _run(args);
  }
  return 0;
}
Module['callMain'] = Module['run'] = Module.run = run;

function exit() {
  ABORT = true;
  STACKTOP = initialStackTop;

  postMain();

  exitRuntime();

  postRun();
}
Module['exit'] = Module.exit = exit;

#if BUILD_AS_WORKER

var buffer = 0, bufferSize = 0;
var inWorkerCall = false, workerResponded = false, workerCallbackId = -1;

onmessage = function(msg) {
  var func = Module['_' + msg.data['funcName']];
  if (!func) throw 'invalid worker function to call: ' + msg.data['funcName'];
  var data = msg.data['data'];
  if (data) {
    if (!data.byteLength) data = new Uint8Array(data);
    if (!buffer || bufferSize < data.length) {
      if (buffer) _free(buffer);
      bufferSize = data.length;
      buffer = _malloc(data.length);
    }
    HEAPU8.set(data, buffer);
  }

  inWorkerCall = true;
  workerResponded = false;
  workerCallbackId = msg.data['callbackId'];
  if (data) {
    func(buffer, data.length);
  } else {
    func(0, 0);
  }
  inWorkerCall = false;
}

#endif