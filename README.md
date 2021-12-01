# Overview
**Important** This is designed to be used as a template. Take a look at the .inc and, especially, the "Using the Template" part!

Since macros like $$$LOGINFO, $$$LOGSTATUS and so on are only available in Ensemble enabled namespaces, having a fallback logging strategy can be useful, especially for development purposes.

This template was created for this use case specifically. You can use it while working with Cache without Ensemble, while messing around in ZAUTHENTICATE or while debugging things in namespaces where Ensemble is not available.

## Using the Template
Using the template is quite simple:
1. Copy the code of the HBT.DemoLogging.inc into an include (.inc) file, for example MyApplication.Logging.inc
2. Change the routine name (HBT.DemoLogging) to the name you chose for the file minus the .inc, for example MyApplication.Logging
3. Find and replace on this file, replace *HBT.DemoLog* with the name your logging global is supposed to have, for example MyApplication.Log
4. Find and replace on this file, replace LogDemo with the name you want your macros to have, for example LogMyApplication
5. Save and Compile

## Usage
Once you have compiled the Routine, assuming you named it MyApplication.Logging, you can include it like any other macro:
`include (HBT.DemoLogging)`
And then you have access to the following macros:
* $$$LogMyApplicationError
* $$$LogMyApplicationWarn
* $$$LogMyApplicationInfo
* $$$LogMyApplicationDebug
* $$$LogMyApplicationTrace

Which you can call like this:
```
set tResult = <some-of-your-code-that-does-something>
$$$LogMyApplicationInfo("Result of my code is: "_tResult)
```

## Enabling Logging
By default, not log output is written. You will have to enable it first, with a level you want to choose. Levels go from Off (0) to Trace (5), and a higher log level always includes all the lower ones. 

To enable logging, open an IRIS session in the namespace you want to use it in, and execute this:

`set ^MyApplication.Log = 5`

where MyApplication.Log is the name of the global you chose. This will set the logging level to 5, which is trace (See the macro file for a list of logging levels and their numbers)

To disable logging, you can either kill the global (kill ^MyApplication.Log) or set the logging level to off (set  ^MyApplication.Log = 0). The first will also remove the log history, the second will preserve it and just not log more.

## Other
Please let me know if you have any improvements for this. Feel free to comment on the gist, fork or do whatever you want with this!

