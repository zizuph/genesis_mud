inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
  set_name("pitchfork");
  set_long("A large unwieldy pitchfork.\n");
  set_adj("unwieldy");
    set_short("unwieldy pitchfork");
    set_pshort("unwieldy pitchforks");
  set_hit(27);
  set_pen(40);

  set_wt(W_POLEARM); 
  set_dt(W_IMPALE); 

  /* Last, how shall it be wielded? */
  set_hands(W_BOTH);

  add_prop(OBJ_I_WEIGHT, 20000);
/* 
  add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
  add_prop(MAGIC_AM_ID_MAGIC,({10,"strong magic aura"}));
*/

  add_prop(OBJ_I_VALUE, 2000);
/*
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
*/
  add_prop(OBJ_I_VOLUME, 9000);
/*
  add_prop(OBJ_I_WIZINFO, "@@wizinfo");
*/
}

wizinfo() {
  return ("This is a large unwieldy pitchfork. It has become enchanted\n"+
          "by a slow seeping infusion of the gardeners magic aura. Wielded\n"+
        "in the right hands it can be a fearsome weapon.\n");
}
/* This function is called each time the weapon try to hit something */
int
try_hit(object ob) /* ob is the target we will try to hit. */
{
  int strength;
  strength = query_wielded()->query_stat(1);
  if ( strength < 80 ){
    query_wielded()->catch_msg("The pitchfork is to unwieldy for a creature "+
			       "with your puny strenth.\n");
    return 0;
  }
  return 1;			/* Try hit */
}

/* After we triued to hit something this function is called with the result. */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	int phit, int dam)
{
  if (phurt == -1)
    {
      query_wielded()->catch_msg("You manage to hit empty air with the " +
				 "pitchfork.\n");
      enemy->catch_msg("You narrowly escape the big pitchfork.\n");
    }
  else if (phurt == 0)
    {
      query_wielded()->catch_msg("You just manage to scratch " + 
				 enemy->query_nonmet_name() + ".\n");
      enemy->catch_msg("You get a very small scratch from the big pitchfork"+
		       ".\n");
    }
  else
    {
      query_wielded()->catch_msg("You skewer your enemy on the " +
				 "pitchfork.\n");
      enemy->catch_msg("The pitchforks tines makes three neat holes "+
		       "in your body.\n");
    }

  return 1;
}

