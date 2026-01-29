inherit "/d/Genesis/lib/craftsman";
 inherit "/d/Emerald/std/emerald_monster.c";

 void create_emerald_monster()
{
    set_name(({"cloakmaker","npc"}));

    set_race_name("elf");
    set_stats(({ 40, 60, 30, 90, 50, 50 }));

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "cloak" }));

     // the file for the item to clone
     craftsman_set_item_file("/d/Emerald/zaeah/testcloak");
 
     // time in seconds to complete creation of the item
     craftsman_set_time_to_complete(30);
 
     // the cost of an item (in cc)
     craftsman_set_item_cost(800);

     // attributes for the items with possible values
     craftsman_add_attribute("material", ({ "leather", "silk", "velvet" }));
     craftsman_add_attribute("color", ({ "ivory", "purple", "grey" }));
     craftsman_add_attribute("quality", ({ "crude", "splendid", "shoddy" }));
 }

 void init_living()
 {
     ::init_living();
 
     // add the craftsman's commands
     craftsman_init();
 }
 
 void craftsman_configure_item(object who, object ob, mapping attrs)
 {
     ob->set_adj(m_values(attrs));

     switch(attrs["material"])
     {
         case "leather":
             ob->set_ac(10);
             break;
         case "silk":
             ob->set_ac(2);
             break;
         case "velvet":
             ob->set_ac(4);
             break;
         case "wool":
             ob->set_ac(6);
             break;
     }
 }
