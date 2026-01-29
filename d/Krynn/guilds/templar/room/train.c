/*
 * Templar Training Room
 * Louie 2004 with help from Blue Dragonarmy.
 */

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "../local.h"

inherit "/lib/skill_raise";
inherit GUILD_IR;


/*
 *  Prototypes
 */
void set_up_skills();
int check_member();

void
reset_guild_room()
{
    setuid();
    seteuid(getuid());

}

void
create_guild_room()
{
    set_short("practice room in the Templar Knight headquarters");
    set_long("This room is used by Templar Knights to learn "+
        "and improve their abilities.  It is a large room with a "+
        "dirt floor, and many implements of training that are used "+
        "to improve skills.\n");

    add_item(({"implements","tools","floor","dirt floor"}),
      "The dirt floor here contains various implements of training, "+
      "such as practice dummies and posters on different attack styles.  "+
      "These make it possible to <learn> or <improve> Templar Knight "+
      "fighting abilities.\n");
    add_item(({"poster","posters"}),
      "The posters detail ways to brutally attack an opponent with "+
      "surprise blows and how to avoid being hit during combat.\n");
     
    add_item(({"dummies","dummy","practice dummy","practice dummies"}),
      "The dummies are used to perfect damaging attacks used in combat.\n");

    add_exit(ROOM+"hallway1","west",check_member);
    
    create_skill_raise();
    set_up_skills();
    reset_guild_room();
}

void
init()
{
    init_skill_raise();
    ::init();
}

int
check_member()
{

    if (TP->query_wiz_level())
    {
        return 0;
    }
    
    if (!ADMIN->query_member(TP)
        && !TP->query_pot_member())
    {
        write("Several guards suddenly appear and throw "+
            "you out of the building!\n");
        tell_room("Several guards suddenly appear "+
            "and throw "+QTNAME(TP)+
            " out of the room!\n", TP, TP);
        TP->move_living("M",ROOM+"joinroom",1,0);
        return 1;
    }
    
    return 0;
}

void
set_up_skills()
{
    sk_add_train(SS_WEP_CLUB, "fight with clubs",       0,0,50 );
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed",      0,0,50 );
    sk_add_train(SS_DEFENCE,   "survive in combat",     0,0,50 );
    sk_add_train(SS_PARRY,  "parry with a weapon",      0,0,50 );
    sk_add_train(SS_BLIND_COMBAT,  "fight in the dark", 0,0,50 );
    sk_add_train(SS_APPR_MON,  "appraise enemies",      0,0,60 );
    sk_add_train(SS_TRACKING,  "track prey",            0,0,45 );
    sk_add_train(SS_LOC_SENSE, "be aware of locations", 0,0,60 );
    sk_add_train(SS_LANGUAGE,  "understand and speak languages", 0,0,60 );
    sk_add_train(SS_AWARENESS,  "be aware",             0,0,60 );
    
    sk_add_train(SS_GUILD_ATTACK_SKILL, "deliver a brutal attack",
        "tattack",100,100,SS_LAYMAN,100);
    sk_add_train(SS_GUILD_SAP_SKILL, "sap opponents",
        "sap",100,100,SS_LAYMAN,100);
    sk_add_train(SS_GUILD_DEFEND_SKILL, "focus on avoiding attacks",
        "focus",100,100,SS_LAYMAN,100);
    
}


int
sk_improve(string str)
{
    if (TP->query_guild_name_lay() == GUILD_NAME)
    {
        return ::sk_improve(str);
    }
    
    write("You must be a Templar Knight to train here.\n");
    return 1;
    
}
