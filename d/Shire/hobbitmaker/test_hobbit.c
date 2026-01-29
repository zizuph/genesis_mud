#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

#define HOBBIT_ARM_DIR "/d/Shire/moria/arm/"
#define HOBBIT_WEP_DIR "/d/Shire/moria/wep/"

void
create_hobbit()
{
    set_type(MAIDEN);
    set_power(200);

    set_long(0);
    set_title("the Notorious Hobbitmaker of the Shire");

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
