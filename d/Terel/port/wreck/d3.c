inherit "/d/Terel/port/wreck/udeck";

#define WRECK     "/d/Terel/port/wreck/"
#define MON       "/d/Terel/port/monster/"
#define MONSTER   ({MON+"octo", MON+"hummer", MON+"hummer", MON+"squid"})

public void
create_udeck()
{
    int i;
    
    set_long("You are standing in waist-deep water under deck. " +
             "There is not much left here. Perhaps everything of value " +
             "has disappeared into the water.\n");

    add_item(({"water"}), "It feels very cold.\n");
    
    set_vol_limit(20000);
    
    for (i=0; i<sizeof(MONSTER); i++) add_monster(MONSTER[i]);

    add_exit(WRECK + "d2", "west", 0, 10);
}


