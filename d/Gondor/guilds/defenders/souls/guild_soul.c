/* /d/Gondor/guilds/defenders/shadows/guild_soul.c
 *
 * The guild soul
 *
 *
 * Nerull 2016
 */


inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>


object wield_par;


public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "defenders"; }


public mapping
query_cmdlist()
{
    return ([

"defhelp"                : "s_defhelp",
"deflist"                : "deflist",
"deftitles"              : "do_deftitles",
"defgrin"                : "do_defgrin",
"defobserve"             : "do_defobserve",
            ]);
}



int
do_deftitles()
{

       write("\n");
       write("\n");
       write("   @--------------------------------------@\n");
       write("   |                                      |\n");
       write("   |       Defenders of the Westlands     |\n");
       write("   |   ================================   |\n");
       write("   |                                      |\n");
       write("   | Title 1                              |\n");
       write("   | Title 2                              |\n");
       write("   | Title 3                              |\n");
       write("   | Title 4                              |\n");
       write("   | Title 5                              |\n");
       write("   |                                      |\n");
       write("   |                                      |\n");
       write("   @--------------------------------------@\n");
       write("\n");
       write("\n");

    return 1;

}



int
s_defhelp()
{

    write("  _____________________________________\n");
    write(" |                                     |\n");
    write(" |          > Defenders Help <         |\n");
    write(" |                                     |\n");
    write(" |   Emotes                            |\n");
    write(" |   --------------                    |\n");
    write(" |   defgrin                           |\n");
    write(" |   defobserve                        |\n");
    write(" |                                     |\n");
    write(" |                                     |\n");
    write(" |   commands                          |\n");
    write(" |   --------------------              |\n");
    write(" |   defhelp                           |\n");
    write(" |   deflist                           |\n");
    write(" |   deftitles                         |\n");
    write(" |                                     |\n");
    write(" |_____________________________________|\n");

  	return 1;
}

public int
deflist(string str)
{
	setuid(); seteuid(getuid());

	MEMBER_LIST_UTILITY->list_members();

	return 1;
}


int
do_defobserve(string str)
{
    object *targ;
    notify_fail("Observe whom?\n");
    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
        return 0;

    actor("You observe",targ," as if taking measure of "
	+targ[0]->query_possessive()+" body-parts " +
    "for your private collection.");
    targetbb(" observes you, as if taking measure of your body-parts " +
    "for "+this_player()->query_possessive()+" private collection.",targ);
    all2actbb(" observes",targ," as if taking measure of "
	+targ[0]->query_possessive()+" body-parts " +
    "for private collection.");
    return 1;
}


int
do_defgrin(string str)
{
    object *targ;
    notify_fail("Grin at whom?\n");
    targ = parse_this(str,"[at] %l");
    if(!sizeof(targ))
        return 0;
    actor("You grab hold of the back of your hair pulling hard, outlining the " +
    "features of your skull as you grin broadly at",targ,".");
    targetbb(" grabs hold of the back of "
	+this_player()->query_possessive()+" hair " +
    "pulling hard, outlining the features of "
	+this_player()->query_possessive()+" skull as "
	+this_player()->query_pronoun()+" grins " +
    "broadly at you.",targ);
    all2actbb(" grabs hold of the back of "
	+this_player()->query_possessive()+" hair " +
    "pulling hard, outlining the features of "
	+this_player()->query_possessive()+" skull as "
	+this_player()->query_pronoun()+" grins " +
    "broadly at",targ,".");
    return 1;
}



























