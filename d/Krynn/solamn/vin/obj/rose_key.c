// rose_conclave_key
// grace sept 1994

inherit "/std/key";
#include "/d/Krynn/common/defs.h"
#include "../knight/guild.h"
#include <stdproperties.h>
#include <macros.h>

#define ROSE_C_KEY    19941205

create_key() 
{
    ::create_key();

    set_name("rose_conclave_key");
    add_name("key");
    set_adj(({"ornate", "gold"}));
    set_pshort("ornate gold keys");
    set_key(ROSE_C_KEY);
    set_short("ornate gold key");
    set_long("A key wrought from gold in the shape of a rose. "+
      "It is the property of the High Knight of Rose, and opens "+
      "the Rose Conclave Door.\n");

    add_item("rose", "It looks like the Rose Carved into the door "+
        "of the Rose Conclave office.\n");

    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(MAGIC_AM_MAGIC,({5,"enchantment"}));
    add_prop(OBJ_S_WIZINFO, "A key which magically appears in the "+
        "hands of Conclave Members who do not have one upon entering "+
        "/d/Krynn/solamn/hctower/spur/room/kn1 through the room to "+
        "east.  It opens the Rose Conclave Door.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
	"A key which belongs to the High Knight of the Rose and "+
        "will magically remove itself if in another's inventory.\n", 0}) );
}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
        {
            set_alarm(2.0, -1.0, "destroy_key");
            return;
        }
}

void 
destroy_key()
{
    TP->catch_msg("Paladine is displeased. The ornate key crumbles to dust.\n");
    set_alarm(1.0, 0.0, "remove_object");    
    return;
}
