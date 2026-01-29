inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Rhovanion/defs.h"
void do_add_see();
void do_rem_see();
int i_am_broken = 1;
void
create_weapon() {
   set_name("axe");
   set_adj("razor");
   set_adj("feorol");
   set_short("feorol razor axe");
   set_long("This is the axe used by gnomes while mining in dangerous " +
      "or unexplored tunnels (known for not being useful unless in " +
      "perfect condition).  Its small size makes it especially " +
      "useful for combat in areas where there isn't much room to " +
      "swing.  The handle is so light you gather it must be hollow, " +
      "but seeing that it is constructed of high grade steel you " +
      "don't think it will be broken easily. What catches your eye, " +
      "though, is the blade of the axe for it is made of a very " +
      "reflective metal the likes of which you've never seen before. " +
      "Perhaps an alloy made with magic you think... and looking " +
      "closer you think you notice a slight glow from the blade. " +
      "In addition to the single blade of the axe there is a sharp " +
      "pick of that same reflective alloy protruding from the back of " +
      "the blade.  By the looks of this weapon you've obtained quite " +
      "an item.\n");
   
   add_prop(OBJ_I_WEIGHT, 2200);
   add_prop(OBJ_I_VOLUME, 1900);
   set_hit(35);
   set_pen(35);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   set_wf(TO);
   set_dull(1);
}
int
wield()
{
   if (i_am_broken)
      do_add_see();
   return -1;
}
int
set_repair_dull(int rep)
{
   i_am_broken = 0;
   do_rem_see();
   ::set_repair_dull(rep);
}
void
do_add_see() {
   seteuid(getuid());
   TO->add_my_desc("You also notice the blade of the axe is slightly detached from the handle, but that's nothing a skilled smith can't take care of.\n");
}
void
do_rem_see() {
   seteuid(getuid());
   TO->remove_my_desc();
}
