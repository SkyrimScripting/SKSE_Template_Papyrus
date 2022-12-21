scriptName MyNativeFunctions hidden
{
    Some native functions implemented in C++!
}

function PrintConsole(string text) global native
{Print to the ~ Skyrim console}

function PrintLog(string text) global native
{Print to the log file of the SKSE plugin which implements this function}

string function GetString() global native
{Returns a string!}
