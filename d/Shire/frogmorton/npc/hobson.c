#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

#define HOBBIT_ARM_DIR "/d/Shire/moria/arm/"
#define HOBBIT_WEP_DIR "/d/Shire/moria/wep/"

void
create_hobbit()
{
    set_type(SHIRRIFFE);
    set_power(100);

    set_name("hobson");
    add_name("_hobson_");
    set_adj("smart");
    set_adj("talkative");
    set_long("This is the Head Shirriffe of the East " +
        "Farthing wh oversees the Bounders in this part of the " +
        "Shire. He's responsible for keeping the peace and making " +
        "sure there no one causes any mischief.\n");
    set_title("the Head Shirriffe of East Farthing");

}

void
introduce_hobbit(string who)
{
    command("introduce me");
    command("say Hello there, my name is "+query_met_name()+"!");
}

void
arm_hobbit()
{
    setuid(); seteuid(getuid());
    clone_object(HOBBIT_ARM_DIR+"hauberk")->move(TO);
    clone_object(HOBBIT_WEP_DIR+"orcscim")->move(TO);
    command("wield all");
    command("wear all");
}
