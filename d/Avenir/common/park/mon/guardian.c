// Guardian      /d/Avenir/common/park/mon/guardian.c
// creator(s):   Ilyian (from file by Farlong)
// last update:  Lilith, 8 Nov 97: Fixed alarm bug in attacked_by()
//               Gorboth, 6 Oct 14: changed race "creature" to "human"
//               Vyasa, 1 Jan 17: added name 'creature' for intuitive design
// purpose:      Guards the fountain in the park
// note:
// bug(s):
// to-do:

inherit "/std/monster";

#include "/d/Avenir/common/common.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>

int    alarm_id;
object ml, mr;

void
create_monster()
{
    set_name("guardian");
    add_name(({"W_am_guard"}));
    add_name(({"creature"}));
    set_short("twisted creature");
    set_race_name("human");
    set_adj("twisted");
    set_gender(G_NEUTER);
    set_alignment(0);
    set_long("This horrible creature may have once been humanoid, "
        +"but has since been twisted into this horrible form "
        +"by some unnatural force. Its eyes stare out blankly "
        +"and it seems to have completely lost its mind.\n");

    add_prop(CONT_I_WEIGHT, 444*1000);
    add_prop(CONT_I_HEIGHT, 689);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_SEE_DARK,6);

    set_stats(({120,91,140,10,10,140}));

    add_prop(LIVE_I_QUICKNESS, 100);
    set_skill(SS_UNARM_COMBAT, 130);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_2H_COMBAT, 90);
    set_skill(SS_WEP_SWORD, 85);
    set_skill(SS_AWARENESS, 60);
    set_pick_up(1);
    set_attack_chance(85);

    set_act_time(10);
      add_act("smirk");
      add_act("growl");
      add_act("frown");
      add_act("emote peers intently around.");
      add_act("laugh craz");
      add_act("emote twists itself into a contorted position");
      add_act("scream");

    set_cact_time(2);
      add_cact("scream");
      add_cact("emote lets out a piercing howl of pure rage.");
      add_cact("emote thrashes around wildly in a mindless fury.");
      add_cact("snarl all");
      add_cact("wield all");
      add_cact("cackle");
      add_cact("glare evil enemy");
      add_cact("swing maquahuitl");
      add_cact("spin maquahuitl");
}

void
equip_me()
{
     object garmour;
     seteuid(getuid(this_object()));

     garmour = clone_object(PK+"obj/g_armour.c")->move(this_object());
     ml = clone_object(PK+"obj/maquahuitl_l.c");
     ml->move(this_object());
     mr = clone_object(PK+"obj/maquahuitl_r.c");
     mr->move(this_object());
     command("wear all");
}

void 
return_to_normal()
{
    if (TO->query_attack())
    {
        command("swing maquahuitl");
        return;
    }
    command("unwield all");
    command("snarl");
    command("emote sheathes its weapons on its back.");
    remove_alarm(alarm_id);
    alarm_id = 0;
}

void 
attacked_by(object ob)
{
    ::attacked_by(ob);

    /* Do nothing if the weapons are wielded or the alarm_id exists */
    if (ml->query_wielded() == this_object())
        return;
    if (mr->query_wielded() == this_object())
        return;
    if (alarm_id)
        return;

    alarm_id = set_alarm(10.0, 60.0, return_to_normal);
    command("emote draws a pair of strange swords from sheathes on its back.");
    command("scream");
    command("wield all");
}

