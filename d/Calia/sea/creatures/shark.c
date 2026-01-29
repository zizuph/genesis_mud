
 /*  
  
    A shark for the water area

    coder(s):    Amelia

    history:    7.5.95    created                    Amelia
               22.7.95    header added               Digit
               18.8.97    added set_restrain_path    Jaacar
               19.9.97    changed special to use
                          switch                     Jaacar
              31/10/99    fixed leftover names,
                          took out tell_watcher      Maniac
 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "defs.h"

#define A_BITE  0
#define A_JAWS 1
#define A_TAIL 2

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_EYES 3


void
create_creature()
{
	set_name("jaws");
	set_race_name("shark");
    set_short("great white shark");
    set_pshort("great white sharks");
    set_adj(({"great", "white"}));
    set_long("This is the infamous great white shark. It is very large, "+
        "long and bullet shaped. It's black eyes appear lifeless "+
        "and evil. It is always hungry and will eat anything...or anyone. "+
        "You feel yourself in great danger...\n");

	set_stats(({110, 100, 100, 15, 15, 145}));

    add_leftover(SEA_LEFTOVERS+"shark_meat", "meat", random(3) + 1, 0, 0, 1);
    add_leftover(SEA_LEFTOVERS+"shark_tooth", "tooth", random(8) + 2, 0, 0, 1);
    add_leftover(SEA_LEFTOVERS+"shark_eye", "eyeball", random(1) + 1, 0, 0, 1);
    add_leftover(SEA_LEFTOVERS+"shark_fin", "fin", 1, 0, 0, 1);

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_LOOKS,1);
    set_gender(2);
	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);
	set_aggressive(1);
	set_alignment(-500);

	set_attack_unarmed(A_JAWS, 40, 50, W_IMPALE, 45, "jaws");
	set_attack_unarmed(A_BITE, 35, 45, W_SLASH, 45, "teeth");
	set_attack_unarmed(A_TAIL, 20, 25, W_BLUDGEON, 10, "tail");

    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 15, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
    set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eye");
	add_act("emote swims around in circles.");
	add_act("emote eyes you hungrily.");

    set_random_move(15);
    set_restrain_path(({(SECTOR_PATH(0, 0, 1)),(SECTOR_PATH(0, 0, 2)),
        (SECTOR_PATH(0, 0, 3)),(SECTOR_PATH(0, 0, 4)),
        (SECTOR_PATH(0, 10, 1)),(SECTOR_PATH(0, 10, 2)),
        (SECTOR_PATH(0, 10, 3)),(SECTOR_PATH(0, 10, 4)),
        (SECTOR_PATH(10, 10, 1)),(SECTOR_PATH(10, 10, 2)),
        (SECTOR_PATH(10, 10, 3)),(SECTOR_PATH(10, 10, 4)),
        (SECTOR_PATH(10, 0, 1)),(SECTOR_PATH(10, 0, 2)),
        (SECTOR_PATH(10, 0, 3)),(SECTOR_PATH(10, 0, 4))}));
}


int
special_attack(object enemy)
{
    object me;
	mixed *hitresult;
    string how1, how2, my_name, his_name;


    me = this_object();
    if(random(10))
	return 0;                         /* Continue with the attack. */

	hitresult = enemy->hit_me(random(35)+30, W_IMPALE, me, -1);
    my_name = QCTNAME(me);
    his_name =  QTNAME(enemy);

    switch(hitresult[0])
    {
        case -1:
        {
            how1 = my_name+" attempts to bite you but misses.\n";
            how2 = my_name+" attempts to bite "+his_name+" but misses.\n";
            break;
        }
        case 0..4:
        {
            how1 = my_name+" nibbles hungrily at your flesh grazing "+
                "you slightly.\n";
            how2 = my_name+" nibbles hungrily at "+his_name+"'s "+
                "flesh.\n";
            break;
        }
        case 5..9:
        {
            how1 = my_name+" rakes your flesh with its "+
                "daggerlike teeth drawing blood.\n";
            how2 = my_name+" rakes "+his_name+"'s flesh with its "+
                "daggerlike teeth drawing blood.\n";
            break;
        }
        case 10..14:
        {
            how1 = my_name+" slashes you deeply!  Blood flows everywhere!\n";
            how2 = my_name+" slashes "+his_name+" deeply!  Blood "+
                "flows everywhere!\n";
            break;
        }
        case 15..19:
        {
            how1 = my_name+" opens its jaws wide and savagely "+
                "tears your flesh!\n";
            how2 = my_name+" opens its jaws wide and savagely "+
                "tears at "+his_name+"'s flesh!\n";
            break;
        }
        default:
        {
            how1 = my_name+" rips at you fiercely with its "+
                "terrifying teeth, nearly disemboweling you!\n";
            how2 = my_name+" rips fiercely at "+his_name+
                ", nearly disemboweling "+his_name+"!\n";
        }
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);

    enemy->catch_msg(how1);
    tell_watcher(how2, enemy);

    return 1;
}
