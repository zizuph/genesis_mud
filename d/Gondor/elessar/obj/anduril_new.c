/* fices by Olorin, July 1993 */
inherit "/std/weapon.c";
#include "/sys/wa_types.h";
#include "/d/Gondor/defs.h"

int magic_hit;
object hilt, blade;

create_weapon() 
{
	set_name("Anduril");
	set_name("anduril");
	set_name("sword");
	set_hands(W_RIGHT);
	set_wt(W_SWORD);
	set_dt(W_SLASH);
	set_hit(25);
	set_pen(25);
	
	set_short("Elessar's sword Anduril");
	set_long("It's the Anduril, the Sword that was broken!\n" +
		 "It is now forged anew by Elrond's elves, and is\n" +
		 "Elessar's trusted weapon against the evils forces.\n" +
		 "The contours of a tree surrounded by seven stars\n" +
		 "are engraved in the blade.\n");
        set_wf(this_object());

	magic_hit = 200;

}

weapon_hit()
{

	if (!magic_hit)
		return;
	if (random(5) == 0)
	{
		magic_hit--;

		write("You shout 'By Elendil!!' as you hit your foe.\n");
		say("You feel a stunning shock as the sword Anduril hits you!\n");
		this_player()->query_attack()->hit_player(random(15) + 5);
	      }
	if (!magic_hit)
	{
		write("Your sword, Anduril breaks in two pieces!!\n");
		blade = clone_object("/d/Gondor/elessar/obj/blade");
		hilt = clone_object("/d/Gondor/elessar/obj/hilt");
    blade->move(TP);
    hilt->move(TP);
		unwield_wep();
    TO->remove_object();
	}
}

wield()
{

	if(magic_hit)
		write("You feel a magical shock rush through your body!\n");
	return 0;
	
}

set_magic_hit(val)
{
  if (!val) {
    write("The sword doesn't seem to be out of the ordinary.\n");
    magic_hit = 1;
    return 1;
    }
  write("The blade of the sword is surrounded by flames for a moment.\n");
  magic_hit = val;
  return 1;
}

unwield()
{

	if(magic_hit)
		write("You feel less powerful now.\n");
	return 0;	
}
