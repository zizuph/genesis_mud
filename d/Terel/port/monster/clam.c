/*
 * clam.c
 *
 * A clam. Mortricia Dec 1994
 */

#include "/d/Terel/include/Terel.h"
inherit STDCREATURE;
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <money.h>

#define COLS   ({"black", "blue", "white", "grey"})
#define SIZE   ({"tiny", "small", "normal-sized", "large", "huge"})
#define PEARL  "/d/Terel/port/beach/pearl"

int size;

/*
 * Function name: create_creature
 * Description:   Create the clam.
 */
public void
create_creature()
{
    string adj, str;
    int stat;
    object pearl;
    
    if (!IS_CLONE)
        return;

    ::create_creature();
    
    adj  = COLS[random(sizeof(COLS))];
    size = random(sizeof(SIZE));
    stat = 4*size;
    str = SIZE[size];
    
    set_name("clam");
    set_long("It's a " + adj + " clam. It is " + str +
             ". Maybe it contains a pearl?\n");
    set_adj(str);
    add_adj(adj);
    set_race_name("clam");
    set_stats(({4+stat, 3+stat, 10+stat, 3+size, 3+size, 5+stat}));
    SET_MAX_HP;
    set_alignment(random(10*(size+1))-5*(size+1));
    set_gender(NEUTER);

    set_act_time(10);
    add_act("@@do_wave");

    set_skill(SS_DEFENCE, 5 + random(stat));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_WEIGHT,      300 + size*2000);
    add_prop(CONT_I_VOLUME,      500 + size*2000);
    add_prop(CONT_I_MAX_WEIGHT,  700 + size*2000);
    add_prop(CONT_I_MAX_VOLUME, 1000 + size*2000);

    add_item(({"shell"}),  "It is wet.\n");
    
    seteuid(getuid());
    
    switch (size) {
      case 4:
        if (random(4) == 0) {
          pearl = clone_object(PEARL);
          pearl->set_adj("large");
          pearl->add_adj(adj);
          pearl->add_prop(OBJ_I_VALUE, 128+random(20));
          pearl->move(TO, 1);
        } else
          MONEY_MAKE_SC(3+random(3))->move(TO, 1);
      case 3:
        if (random(3) == 0 && !pearl) {
          pearl = clone_object(PEARL);
          pearl->set_adj("small");
          pearl->add_adj(adj);
          pearl->add_prop(OBJ_I_VALUE, 64+random(10));
          pearl->move(TO, 1);
        } else
          MONEY_MAKE_SC(2+random(3))->move(TO, 1);
      case 2:
        if (random(2) == 0 && !pearl) {
          pearl = clone_object(PEARL);
          pearl->set_adj("tiny");
          pearl->add_adj(adj);
          pearl->add_prop(OBJ_I_VALUE, 32+random(5));
          pearl->move(TO, 1);
        } else
          MONEY_MAKE_SC(1+random(3))->move(TO, 1);
      case 1:
        MONEY_MAKE_CC(3+random(5))->move(TO, 1);
      case 0:
        MONEY_MAKE_CC(1+random(5))->move(TO, 1);
      default:
    }
}

#define A_BITE  0

#define H_SHELL 0

public void
cr_configure()
{
    add_attack( 2+3*size,  5+5*size, W_BLUDGEON, 100, A_BITE);

    add_hitloc( ({ 5+4*size, 5+4*size, 10+5*size }), 100, "shell",  H_SHELL);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
    case A_BITE:
        return "shell";
    }
}

do_wave()
{
    tell_room(ETO, "The " + short() + " opens and closes its shell.\n");
    return "";
}
