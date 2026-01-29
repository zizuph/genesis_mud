/*
   gully_ghost.c
   -------------

   Coded ........: 95/05/03
   By ...........: Jeremiah

   Latest update : 95/05/08
   By ...........: Jeremiah

   This ghost has the map needed to solve the Pax Tharkas prisoner 
   quest. He is looking for evidence, that his ancestors fought in
   the battle defending Pax Tharkas against Fistandantilus army.
   Give him the diary page, found in the private_quarters of Lord
   Verminaard, and he will give you the map.

*/


#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit M_FILE

inherit "/std/act/domove"; /* allows ghost to move */ 
inherit "/std/act/action"; /* allows ghost to act  */

#define I_FOUND_MAP  "_i_found_pax_map"

object map;

void
create_krynn_monster()
{
    int i;

    set_name("ghost");
    set_race_name("dwarf");
    set_long("This is the ghost of a gully dwarf. He constantly fades " +
      "in and out of focus. Sometimes he is clearly visible, " +
      "other times only a vague shadow in the room. You can " +
      "see right through him.\n");
    add_name("gully");
    add_name("gully ghost");
    set_short("ghost of a dwarf");

    for (i = 0; i < 6; i++)
        set_base_stat(i,10 + random(10));

    set_gender(G_MALE);
    set_default_answer("emote wails: Me not know.", 1);

    set_act_time(3);

    add_act("emote wails: Me never find it.");
    add_act("sigh");
    add_act("emote wails: Must find it before me can rest.");
    add_act("emote wails: Me want to get rest.");
    add_act("emote fades slightly.");
    add_act("emote looks very unhappy.");   

    add_ask(({"it", "help"}), VBFC_ME("it_hint"));
    add_ask("rest", VBFC_ME("rest_hint"));

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(LIVE_I_UNDEAD, 15);

    seteuid(getuid(TO));
}


it_hint()
{
    command("emote wails: Long time ago gullies help fight here.");
    command("emote wails: Gullies stayed with highgug here, me know.");
    command("emote wails: Gullies helped other dwarvies fight here.");
    command("emote wails: Me want to know for sure, then can rest.");

    return "";
} 


rest_hint()
{
    command("emote wails: Me want to rest very much.");
    command("emote wails: Me just need to find it first.");

    return "";
}


public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    ob->catch_msg("As you attack the ghost, it fades away into " +
      "nothingness and disappears, like it had " +
      "never been here.\n");
    tell_room(E(TO), "As " + QCTNAME(ob) + " attacks the ghost, " +
      "it fades away into nothingness and disappears, " +
      "like it had never been here.\n", ob);

    remove_object();      
}


void
right_thing(object ob, object from)
{
    command("emote looks at the " + ob->short() + ".");
    command("emote goes ohhh!");
    command("emote wails: Me not read very well, but this is it.");
    command("emote wails: Now me can go to rest.");
    command("emote wails: Thank you. Me very happy.");
    command("emote wails: Me give you only thing me have.");

    clone_object(POBJ + "quest_map")->move(TO);
    command("give map to " + from->query_real_name());
    from->add_prop(I_FOUND_MAP, 1);

    command("emote smiles, fades slightly, then disappears.");
    remove_object();
}


void
wrong_thing(object ob, object from)
{
    tell_room(E(TO),"The ghost doesn't seem to be able to get hold of it " +
      "and it drops to the floor.\n");

    ob->move(E(TO));
}


public void
enter_inv(object ob, object from)
{
    string *names;

    ::enter_inv(ob, from);
    names = ob->query_names();

    if(sizeof(names) < 3)
        set_alarm(1.0, 0.0, "wrong_thing", ob, from);
    else
    {
        if(names[2] == "_diary_page_")
            set_alarm(1.0, 0.0, "right_thing", ob, from);
        else
            set_alarm(1.0, 0.0, "wrong_thing", ob, from);
    }
}   
