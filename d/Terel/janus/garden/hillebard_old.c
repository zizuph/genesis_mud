inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
  set_name("hillebard");
  set_long("A long hillebard in relatively good shape. The blade at the "+
           "end of the 2.5 meter long pole is shaped like a beak. \n");
  set_adj("long");
    set_short("long hillebard");
    set_pshort("long hillebards");
  set_hit(25);
  set_pen(40);

  set_wt(W_POLEARM); 
  set_dt(W_IMPALE); 

  /* Last, how shall it be wielded? */
  set_hands(W_BOTH);

  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 9000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
}

/* This function is called each time the weapon try to hit something */
int
try_hit(object ob) /* ob is the target we will try to hit. */
{
     int strength;
     strength = query_wielded()->query_stat(1);
     if ( strength < 25 ){
    query_wielded()->catch_msg("The hillebard is to unwieldy for a creature "+
                "with your puny strenth.\n");
    return 0;
  }
    return 1; /* Try hit */
}

/* After we triued to hit something this function is called with the result. */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	int phit, int dam)
{
    if (phurt == -1)
    {
	query_wielded()->catch_msg("You manage to hit empty air with the " +
		"hillebard.\n");
	enemy->catch_msg("You narrowly escape the big polearm.\n");
    }
    else if (phurt == 0)
    {
	query_wielded()->catch_msg("You just manage to scratch " + 
        enemy->query_nonmet_name() + ".\n");
        enemy->catch_msg("You get a very small scratch from the big hillebard"+
		".\n");
    }
    else
    {
    query_wielded()->catch_msg("The hillebard cuts deep into your opponent.\n");
    enemy->catch_msg("The hillebard cuts you badly.\n");
    }

    return 1;
}

