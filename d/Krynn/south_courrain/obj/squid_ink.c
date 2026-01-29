inherit "/std/leftover";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#define SQUID_INK  "/d/Krynn/south_courrain/obj/squid_blind_obj"

int empty;

public int
query_sac_fullness()
{
    return empty;
}

void
create_leftover()
{
    set_name("sac");
    add_name("_giant_squid_ink_sac");
    add_name("ink");
    set_adj("ink");
    add_adj("squid");
    add_adj("collosal");

    set_short("@@short_desc");
    set_long("@@long_desc");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VALUE, 2000);
}

string
short_desc()
{
    if(!empty)
        return "collosal squid ink sac";
    else
        return "empty ink sac";
}

string
long_desc()
{
    if(!empty)
        return "This large muscular bag is the almost-full " +
            "ink sac of a collosal sea squid.\n";
    else
        return "This large muscular bag is the empty " +
            "ink sac of a collosal sea squid.\n";
}

int
do_squeeze(string str)
{
    object ob;

    if(!str)
        return 0;

    if (parse_command(str, this_player(), "%o", ob) && 
        ob == this_object())
    {
        if(empty)
        {
            this_player()->catch_msg("You squeeze the " +
                short()+ ". It makes a rather pathetic " +
                "flubbing noise.\n");
            say(QCTNAME(this_player())+ " squeezes " +
                short()+ ". It makes a rather pathetic " +
                "flubbing noise.\n");
            return 1;
        }

        this_player()->catch_msg("You squeeze " +
            short()+ " and it explodes, ink spraying " +
            "into your face!\n");
        say(QCTNAME(this_player())+ " squeezes " +
            short()+ ", causing it to explode in " +
            this_player()->query_possessive()+ " face!\n");

        seteuid(getuid(this_object()));
        object blind = clone_object(SQUID_INK);
        blind->move(this_player(), 1);
        add_adj("empty");

        empty = 1;
        return 1;
   }

   notify_fail("Squeeze what?\n");
   return 0;
}

void
init()
{
    ::init();
    
    add_action("do_squeeze", "squeeze");
}

/*
 * Function name: query_recover
 * Description  : We allow this standard object to recover.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + empty;
}

void
init_recover(string arg)
{
    int num = atoi(arg);

    if(num) 
        empty = num;
}

