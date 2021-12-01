ROUTINE HBT.DemoLogging [Type=INC]

/// ## Setup ##
/// This is a very simple way to achieve logging where things like the Ens.Log are not available.
/// Logs are written into a global, sequentially, with timestamp, class name and logging level
/// Log levels are be controlled and offer the usual granularity: Off, Error, Warn, Info, Debug and Trace
/// Using this Template:
/// - Copy this code into an include file, for example <YourCompanyName>.Logging.inc
/// - Change the routine name to the name you chose for the file minus the .inc, for example <YourCompanyName>.Logging
/// - Do a find and replace on this file, replace HBT.DemoLog with the name your logging global is supposed to have
/// - Save (and compile)
///
/// ## Using the Logging ##
/// Let's say you kept the original names, you can use this as following:
/// - In your code at the top of the file, you do an "include (HBT.DemoLogging)"
/// - Whenever you want to log something, you can now use the macros: $$$LogDemoInfo("This is an info message")
/// before you see any log output you will have to enable logging for the desired level. To do so, open an IRIS session and execute
/// this in the namespace your logging is happening:
/// - set ^HBT.DemoLog = 3
/// which would set the logging level to Info ($$$LogLevelInfo is 3, see below)
/// To switch logging off you can either:
/// - set ^HBT.DemoLog = 0
/// which would turn off logging but keeps the log history, or:
/// - kill ^HBT.DemoLog
/// which would turn off logging and wipes the entire log history.
/// 
/// ## Viewing the logs ##
/// You can either use "zwrite ^HBT.DemoLog" to view the entire global in an IRIS session, or use the global UI
/// from the IRIS management portal: http://localhost:52773//csp/sys/exp/UtilExpGlobalView.csp?$ID2=HBT.DemoLog&$NAMESPACE=
/// (Url depends on where your IRIS is running)
///
/// ## Usage in Cache and Ensemble ##
/// This was originally made in Cache 2018, so it should work in Cache and Ensemble!

#Define CurrentDate ##class(%Library.UTC).NowUTC()
#Define CurrentClassName $CLASSNAME($THIS)

/// These are just to make the code less cryptic; They are not necessary, and you can replace the values down below with the numbers
#Define LogLevelOff 0
#Define LogLevelError 1
#Define LogLevelWarn 2
#Define LogLevelInfo 3
#Define LogLevelDebug 4
#Define LogLevelTrace 5

/// To get unique subnodes in the logging global, use the same global with the subnode "Counter" combined with $INCREMENT to
/// get unique subnodes.
#Define LogDemo(%msg, %level)   set ^HBT.DemoLog($INCREMENT(^HBT.DemoLog("Counter")))="["_$$$CurrentDate_"]["_$$$CurrentClassName_"]["_%level_"] "_%msg
#Define LogDemoError(%msg)  if ($get(^HBT.DemoLog, $$$LogLevelOff) >= $$$LogLevelError)  { $$$LogDemo(%msg, "Error") }
#Define LogDemoWarn(%msg)   if ($get(^HBT.DemoLog, $$$LogLevelOff) >= $$$LogLevelWarn)   { $$$LogDemo(%msg, "Warn") }
#Define LogDemoInfo(%msg)   if ($get(^HBT.DemoLog, $$$LogLevelOff) >= $$$LogLevelInfo)   { $$$LogDemo(%msg, "Info") }
#Define LogDemoDebug(%msg)  if ($get(^HBT.DemoLog, $$$LogLevelOff) >= $$$LogLevelDebug)  { $$$LogDemo(%msg, "Debug") }
#Define LogDemoTrace(%msg)  if ($get(^HBT.DemoLog, $$$LogLevelOff) >= $$$LogLevelTrace)  { $$$LogDemo(%msg, "Trace") }
