/*
 * grugg.c
 * FIXA
 * Used in carisca/c2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* a nasty grugg - gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

void equip_myself();
void rubrub();
int spit(string s, string ss);

void
default_config_npc(int i)
{
    int j;
    for (j = 0; j < 6; j++)
        set_base_stat(j, i);
}

void
create_creature()
{
    default_config_npc(75);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_name("grugg");
    set_race_name("grugg");
    set_short("nasty grugg");
    set_adj("nasty");

    set_long("This is a nasty grugg from the boiling inside of the earth. " +
             "It looks like a huge centipede, except for the smoke coming " +
             "from its mouth.\n");

    set_alignment(-500);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);

    add_act("say grugg!");

    set_act_time(3);

    set_attack_unarmed(0, 25, 25, W_IMPALE, 60, "jaws");
    set_attack_unarmed(1, 25, 25, W_BLUDGEON, 60, "breath");

    set_hitloc_unarmed(A_HEAD, ({50}), 10, "head");
    set_hitloc_unarmed(A_BODY, ({50}), 80, "body");

    trig_new("%s 'spits' %s", "spit"); //FIXA

    set_alarm(1.0, 0.0, equip_myself);
    set_alarm(1.0, 30.0, rubrub);

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);
}
void
equip_myself()
{
    seteuid(getuid());
    clone_object(ROKEDIR + "obj/dust")->move(TO);
}

void
init_living()
{
    add_action(spit, "spit");
}

int
spit(string s, string ss)
{
    NF("Spit on whom?\n");
    if (s != "grugg" && s != "on grugg" && s != "at grugg")
        return 0;
    if (ss != "on you!\n")
        tell_room(E(TO), "The grugg looks frightened.\n");
    command("scream");
    command("drop dust");
    tell_room(E(TO), "A small puff of smoke comes from the grugg!\n");
    run_away();

    heal_hp(-10);
    return 1;
}

/*
void
emote_hook(string emote, object actor, string adverb)
{
  if (emote != "spit") return;

  actor->catch_msg("There is a bug here. It might take some time to fix, so please be patient.\n");
}
*/

void
skrik(string s)
{
    tell_room(E(TO), s);
}

void
bomb(object ob)
{
    ob->remove_object();
}

void
rubrub()
{
    tell_room(E(TO), "The grugg rubs his feet with dust.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!from)
        return;

    set_alarm(itof(random(4) + 5), 0.0,
              &skrik("The grugg eats the " + ob->query_name() +
                     " and seems to grow a little.\n"));

    default_config_npc(query_average_stat() + 1);
    set_alarm(1.0, 0.0, &bomb(ob));
}
