scriptName CallNativeQuestFunctions extends MyNativeQuestFunctions

event OnInit()
    MyNativeFunctions.PrintConsole("The quest has " + GetAliasCount() + " aliases")
endEvent
