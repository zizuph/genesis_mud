/*
 *  treant.c
 *
 *  This is a treant summoned by 'druid.c', located
 *  inside a temple in Mithas, its special abilities
 *  are a last effort attempt to heal itself ant the
 *  ability to deal room wide damage on anyone who
 *  target the druid.
 *
 *  Created by Carnak, January 2016
 */
 
#pragma save_binary

inherit "/d/Ansalon/std/monster";
inherit "/std/combat/unarmed";
inherit "/d/Krynn/open/auto_teaming";

#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

string *gAdj = ({"gnarled","branchy","moss-covered","leaf-bearing",
                 "broad-leaved","narrow-leaved","oak","pine","elm",
                 "maple"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
        return;

    set_pick_up_team(({"treant","druid"}));
    set_max_team_size_auto_join(6);
	
    set_name("treant");
    set_living_name("_chislev_treant");
    set_race_name("treant");
    set_gender("G_NEUTER");
    
    set_adj("young");
    add_adj(ONE_OF(gAdj));
    
    set_short(implode(query_adjs()," ") + " treant");
    set_long("This is a "+implode(query_adjs()," ")+" treant "+
    "sproutling, having just recently grown from a seed.\n");

    set_stats(({190+random(20),150,190+random(20),50,50,180}));
    set_hp(10000);

    set_attack_unarmed(W_LEFT, 55, 55, W_BLUDGEON, 50,
    "left branch-like arm");
    set_attack_unarmed(W_RIGHT, 55, 55, W_BLUDGEON, 50,
    "right branch-like arm");

    set_hitloc_unarmed(A_HEAD, 50, 15, "bark");
    set_hitloc_unarmed(A_L_ARM, 50, 10, "bark");
    set_hitloc_unarmed(A_R_ARM, 50, 10, "bark");
    set_hitloc_unarmed(A_BODY, 50, 45, "bark");
    set_hitloc_unarmed(A_LEGS, 50, 20, "bark");
	
    set_alignment(0);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 80);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    add_prop(OBJ_I_RES_DEATH, 60);
    add_prop(OBJ_I_RES_POISON, 60);
    add_prop(OBJ_I_RES_FIRE, -50);

}

/*
 * Function     : special_attack
 * Description  : This special attack will harm ALL those who target
 *                the druid, it can also as a last effort try to
 *                restore some of its own health 
 */

int
special_attack(object enemy)
{
    string loc;
    object tar;
    object *enemy_list;
    int i, size;
    string *locations = ({
        "right cheek","left cheek","head", "throat","right arm",
        "left arm", "right shoulder","left shoulder","back","chest"});
    
    if (random(4))
        return 0;
    
    if (this_object()->query_mana()<50)
        return 0;
	
    enemy_list = filter(all_inventory(environment(this_object())),
                 &operator(==)(find_living("_chislev_druid", 0), )
                 @ &->query_attack());

    if (random(3) && this_object()->query_hp()<500)
    {
        this_object()->heal_hp(this_object()->query_mana());
        this_object()->heal_hp(200*sizeof(enemy_list));
        this_object()->add_mana(-(this_object()->query_mana()));
        command("emote gains the blessing of Chislev and regenerates "+
        "some of the damage it has sustained.");
        return 0;
    }
	
    for ( i = 0, size = sizeof(enemy_list); i < size; i++)
    {
        tar = enemy_list[i];
        
        if (!living(tar))
            continue;
        
        if (random(20)>4)
        {
            loc = ONE_OF(locations);
            
            tar->catch_msg("You are struck with great force on the "+loc+
            " by a branch.\n");
            tell_room(environment(tar),QCTNAME(tar) + " is struck with "+
            "great force on the "+loc+" by a branch.\n",tar,tar);
            
            tar->heal_hp(-(250+random(80)));
            if (tar->query_hp() <= 0)
            {
                tar->do_die(this_object());
            }
        }
        else
        {
            tar->catch_msg("You manage to avoid the flailing branches.\n");
            tell_room(environment(tar),QCTNAME(tar) + " manages to avoid the "+
            "flailing branches.\n",tar,tar);
        }
        this_object()->add_mana(-15);
    }
    return 1;
}

public void
do_die(object killer)
{
    write("The "+implode(query_adjs()," ") + " treant "+
    "returns to the earth from whence it came.\n");
    ::do_die(killer);
}


/*
 * Function     : init_team_pickup
 * Description  : This is called so that it will join the other
 *                treants that are summoned, along with the druid
 */
 
void
init_living()
{
    init_team_pickup();
    ::init_living();
}