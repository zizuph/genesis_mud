inherit "/std/workroom";
#include <macros.h>
#include <stdproperties.h>
#include <money.h>


#define TO this_object()
#define PATH "/d/Terel/mecien/valley/city/"
#define HERE "/d/Terel/mecien/valley/hforest/"
#define OBJ "/d/Terel/mecien/valley/guild/obj/"

object ob, ob1, ob2, ob3, ob4, ob5;

create_workroom()
{
   set_short("Barrow");
   set_long(
      "This ancient chamber has walls of carved stone, silvery and ornate. In the " +
      "center of this place is a stone coffin.\n");
   
   add_item(({"carved stone", "stone", "silver stone", "ornate stone"}),
      "It is very beautiful, set with stars and leaves.\n");
   add_item("walls", "They are covered with mosaics.\n");
   add_item("mosaics", "They seem to depict the life of a great knight.\n");
   add_item("knight", "Some warrior of the ancient world.\n");
   add_exit("/d/Terel/mecien/valley/hforest/barrow2", "south", 0);
   
   ob = clone_object(HERE + "coffin");
   ob->move(TO);
   ob1=clone_object("/d/Terel/mecien/valley/city/hauberk");
   ob1->move(ob);
   ob2=clone_object(OBJ + "dagger2");
   ob2->move(ob);
   MONEY_MOVE(random(20) + 1, "gold", 0, ob);
   MONEY_MOVE(random(100) + 20, "silver", 0, ob);
   ob3=clone_object(PATH + "garland");
   ob3->move(ob);
  ob->add_prop(CONT_I_CLOSED, 1);
}
