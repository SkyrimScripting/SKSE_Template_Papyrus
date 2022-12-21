scriptName CallNativeFunctions extends Actor

event OnInit()
    MyNativeFunctions.PrintConsole("Hello console from Papyrus!")
    MyNativeFunctions.PrintLog("Hello log from Papyrus!")
    MyNativeFunctions.PrintLog("The string we got was: " + MyNativeFunctions.GetString())
endEvent
