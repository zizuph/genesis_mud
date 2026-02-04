inherit "/d/Terel/port/wreck/udeck";

#define WRECK     "/d/Terel/port/wreck/"
#define MON       "/d/Terel/port/monster/"
#define MONSTER   ({MON+"squid", MON+"squid", MON+"squid", MON+"squid"})

public void
create_udeck()
{
    int i;
    
    set_long("You are standing in feet-deep water under deck. " +
             "There is not much left here. Perhaps everything of value " +
             "has disappeared into the water. There is an old ladder going " +
             "up.\n");

    add_item(({"water"}), "It feels very cold.\n");

    add_item(({"ladder"}), "It looks unsafe.\n");
    
    set_vol_limit(2000);
    
    for (i=0; i<sizeof(MONSTER); i++) add_monster(MONSTER[i]);

    add_exit(WRECK + "d2",     "east", 0, 5);
    add_exit(WRECK + "cabin",  "up", 0, 3);
}


