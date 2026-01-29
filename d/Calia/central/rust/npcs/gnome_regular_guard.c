/* Created 07/1|/98 by Bishop, of Calia. This is an regular gnome
soldier, who's seen some combat action. */

inherit "/std/monster.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <options.h>
#include <const.h>
#include "defs.h"

#define STATDIFF  20
#define ALIGN   -50

/* Equips him */

void
equip_me()
{
    object armour;
    object armour2;
    object armour3;
    object weapon;

    seteuid(getuid(TO));

    weapon = clone_object(RUST_WEAPONS + "ranseur");
    weapon->move(TO);


    armour = clone_object(RUST_ARMOURS + "double_chainmail");
    armour->move(TO);

    armour2 = clone_object(RUST_ARMOURS + "plate_leggings");
    armour2->move(TO);

    armour3 = clone_object(RUST_ARMOURS + "close_faced_helmet");
    armour3->move(TO);
   
    command("wield all");
    command("wear all");
}


void
create_monster()
{
    int x, y;
    string *guardfeatures, *regularfeatures;

    guardfeatures = ({"vigilant","dark-eyed","wary","attentive",
        "serious","dutiful","calm", "alert", "cautious"});

    regularfeatures = ({"energetic","brutal","muscled", 
        "broad-shouldered","robust"});

    x = random(sizeof(guardfeatures));
    y = random(sizeof(regularfeatures));

    set_race_name("gnome");
    add_name("guard");
    set_short(regularfeatures[y]+" " + guardfeatures[x]+" male gnome");
    add_adj(guardfeatures[x]);
    add_adj(regularfeatures[y]);

    set_gender(G_MALE);

    set_long("This gnome looks like a warrior, and judging from his" +
        " confident stance, a skilled one at that. He has the look of" +
        " one who is used to seeing and employing violence.\n"); 	
        
    set_alignment(ALIGN);

    set_base_stat(SS_STR, 80 + random(STATDIFF));
    set_base_stat(SS_DEX, 100 + random(STATDIFF));
    set_base_stat(SS_CON, 80 + random(STATDIFF));
    set_base_stat(SS_INT, 70 + random(STATDIFF));
    set_base_stat(SS_WIS, 50 + random(STATDIFF));
    set_base_stat(SS_DIS, 90 + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_PARRY, 40);
    set_skill(SS_BLIND_COMBAT, 50);

    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 40000);
    add_prop(CONT_I_HEIGHT, 95);
}


void
notify_attacked(object friend, object attacker)
{
    if (!objectp(query_attack()))
        set_alarm(1.0, 0.0, &command("assist"));
}


void
attacked_by(object enemy)
{
    object *friend;
  
    friend = (object *)query_team_others();

    friend->notify_attacked();
  
    ::attacked_by(enemy);
}

int 
query_option(int opt)
{ 
    if (opt == OPT_UNARMED_OFF) 
        return 1; 
   
    else return
       ::query_option(opt);

}