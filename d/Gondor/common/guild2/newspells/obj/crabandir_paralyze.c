/*
 * File: /d/Gondor/common/guild2/newspells/obj/crabandir_paralyze.c
 * This is to work around the limitations of the /std/paralyze.
 */
inherit "/std/paralyze";

int stop( string str )
{
    if ((query_verb() ==  "cast") &&
        (parse_command( str, ({}), "'palanquendo' %s" )))
    {
        return 0;
    }

    return ::stop( str );
}
