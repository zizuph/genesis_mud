// file name: quar5
// creator: Ilyian (October 9, 1995)
// last update:
// purpose: Quarters in the Infidel Hideout
// note:
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object guard, guard1, guard2, guard3, guard4;
object table, plans;

void
create_room()
{
   quar_long("Using set_long instead");
   set_long("This room appears to be a meeting area. There "
           +"is a long wooden table in the center of the "
           +"room, and a heavy lantern hanging over it "
           +"provides light for the area.\n");
   set_short("meeting room");
   AI(({"table"}),"The table is very large, and is made "
           +"from some sort of dark hardwood. Scattered "
           +"over the table are maps and diagrams of all "
           +"sorts.\n");
   AI(({"lamp","lantern","light"}),"The heavy lamp that hangs "
           +"over the table is smoky and smells strongly of "
           +"kerosine. It makes the entire room hazy with "
           +"the smoke.\n");
   AI(({"map","maps","diagrams","diagram"}),"The maps and "
           +"diagrams on the table seem to be battle plans "
           +"of some sort, with areas of attack and "
           +"weaknesses of the enemy outlined in red.\n");
   hall_exit("16","south");

   reset_room();
}

void
reset_room()
{
    if(!present(table))
    {
       table = clone_object(OBJ + "table");
       table->move(TO);
    }

    if(!present(plans, table))
    {
       plans = clone_object(OBJ + "plans");
       plans->move(table, 1);
    }

   if(!guard)
     {
        guard = clone_object(MON+"guard");
        guard->arm_me();
        guard->set_name("graeson");
        guard->set_title("the Hand of Alphum, Warrior of the Infidels");
        guard->set_skill(SS_AWARENESS, 96);
        guard->set_stats(({160,160,160,160,160,160}));
        guard->move(TO);
        guard->add_act("hmm");
        guard->add_act("say We must remain strong!");
        guard->add_act("say Any weakness on our part will "
                      +"be found and taken adventage of.");
        guard->add_act("say Nevermind that mercenary ... I have "
                      +"people taking care of her as we speak.");
        guard->add_act("say We continue as planned.");
        guard->add_act("say The Tyranny will end ... the Faithful "
                      +"will fall!");
     }
   if(!guard)
     {
        guard1 = clone_object(MON+"guard");
        guard1->arm_me();
        guard1->move(TO);
        guard1->add_act("hmm");
        guard1->add_act("say I would advise caution in "
                      +"these matters.");
        guard1->add_act("say We cannot be too careful ... "
                      +"after all, they have much more "
                      +"manpower than we.");
        guard1->add_act("say You remember what happened to "
                      +"Tyril - I don't want to see that "
                      +"EVER happen again to one of us.");
        guard1->add_act("say The Faithful are misrable, but they "
                      +"are strong!");
     }
   if(!guard2)
     {
        guard2 = clone_object(MON+"guard");
        guard2->arm_me();
        guard2->move(TO);
        guard2->add_act("hmm");
        guard2->add_act("say Why don't we just attack at the "
                       +"next opportunity?");
        guard2->add_act("say Enough talking! Words are meaningless!");
        guard2->add_act("say I'm sick of being patient! We should "
                       +"attack!");
        guard2->add_act("say Just one of our men is worth ten of "
                       +"their wretched elite guard!");
     }
   if(!guard3)
     {
        guard3 = clone_object(MON+"guard");
        guard3->arm_me();
        guard3->move(TO);
        guard3->add_act("say Ask Nochipa ... she will know what "
                       +"to do...");
        guard3->add_act("say Do not discount the Hand of Alphum "
                       +"in these matters ... he is more powerful "
                       +"than we would imagine.");
        guard3->add_act("say The only way we will overthrow these "
                       +"Tyrants is through Divine Intervention.");
     }
   if(!guard4)
     {
        guard4 = clone_object(MON+"guard");
        guard4->arm_me();
        guard4->move(TO);
        guard4->add_act("hmm");
        guard4->add_act("ponder");
        guard4->add_act("say But what if Jadestone finds the "
                       +"hideout first?");
        guard4->add_act("say We will be in trouble if "
                       +"they get wind of our plans...");
        guard4->add_act("say I hear that the High Inquisitor "
                       +"has doubled the bounty on us since "
                       +"last week!"); 
     }

}
