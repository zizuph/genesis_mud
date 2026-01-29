// file name:     gate_overseer.c
// creator(s):    Lilith   09/26/97
// purpose:       Flag down sedan chairs
/*
 * Revisions:
 * 	Lucius, Sep 2017: Changed to use base overseer.
 */
#pragma strict_types

#include "/d/Avenir/include/paths.h"
inherit (CITY + "mon/overseer");


/* Create the npc */
public void
create_monster(void)
{
    loc_str = "heading to the Bath";
    chair_path = CITY + "mon/bath_chair";
    Sadj1 = ({ "lithe","muscular","lean","energetic","smiling" });

    ::create_monster();

    add_act("say I can get you a sedan chair to the Bath");
    add_act("shout Get your rides to the Bath right here.");

    add_ask(({"bath", "chair to bath"}), "@@help_ask@@");

    add_ask(({"ziggurat", "pleasure palace", "chair to ziggurat"}),
	"@@zigg_ask@@");

    add_ask(({"inquisitor", "inquisitor enclave"}), "@@not_ask@@");
    add_ask(({"hegemon", "hegemon enclave"}), "@@not_ask@@");
    add_ask(({"executioner", "executioner enclave"}), "@@not_ask@@");

    add_ask(({"enclave", "enclaves"}),
	"say Which enclave did you want to visit?", 1);
    add_ask(({"bondservant", "servant"}),
	"say Bondservants are used to pull the sedan chairs which "+
	"are used to take you to various places in the city.", 1);
}

public string
not_ask(void)
{
    command("say I'd be happy to call a chair for you...");
    command("say But no chairs to anywhere other "+
	"than the Baths from here.");
    return "";
}

public string
zigg_ask(void)
{
    command("say You'll find sedans heading to the Ziggurat "+
	"on the rainbow path.");
    command("smile .");
    return "";
}
