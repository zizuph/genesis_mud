/* A weapon should always begin with these statements: */

inherit "/std/weapon";
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */
#include "/sys/macros.h"
void
create_weapon()
{
    /* Set the name, short description and long description */
    set_name("dagger");
   set_short("black dagger");
   set_long("This dagger is colored black.  Not just any black, but " +
            "dirty black,\nlike coal.  A large stone, colored a very " +
            "ugly dark red is set\nin the handle of the dagger.\n");

    /* Now, a player can refere to this weapon as 'weapon' and 'dagger'. To
     * distinguish it from other daggers, we want the player to be able to 
     * use 'small dagger' as an id too.
     */
   set_adj("black");

    /* Now we want to set the 'to hit' value and 'penetration value' */
   set_hit(15);
   set_pen(17);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE); /* It's of 'knife' type */
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}

void
enter_env(object dest, object old)
{
	::enter_env(dest, old);
	reset_euid();
    write_file("/d/Terel/common/weapon/clone_log", "Dagger cloned to "+
        MASTER_OB(dest) +"\n");
		
}	