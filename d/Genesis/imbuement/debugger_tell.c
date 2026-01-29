#pragma no_shadow
#define NEW_TELL "/d/Genesis/ateam/aod/imbuement/debugger_tell"

public varargs void
send_debug_message2(string tag, mixed input, string file)
{
    NEW_TELL->send_debug_message2(tag, input, file);
}