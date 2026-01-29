inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

void
create_object()
{
    set_name("bell");
    set_adj(({"giant","black-iron"}));
    set_short("giant black-iron bell");
    set_long("This giant bell is made of blackened iron and "+
     "hangs from the ceiling here. There are many strange and "+
     "ancient markings covering its sides, the largest one "+
     "being a giant grim-looking skull. The eyes of the skull "+
     "glowing a soft purple color. Inside, you see a rope "+
     "hanging down.\n");
    add_item("rope","A long black rope made of rough material. "+
    "It looks like you could pull it if you dared to.\n");
     add_prop(OBJ_M_NO_GET,"Are you mad?!\n");
    seteuid(getuid());
}


int
is_khiraa(object ob)
{
    if(IS_DK(ob) || IS_LP(ob))
        return 1;
    return 0;
}
int
ring_bell(string str)
{
    mapping temp;
    object *k_members;
    NF("Pull what?\n");
    if(str != "rope")
        return 0;
    NF("As soon as you touch the rope, your hand burns with "+
    "intense pain, and you release it!\n");
    temp = restore_map(KHIRAA_DIR(log/seekers));
    if(member_array(TP->query_real_name(),m_indexes(temp)) == -1)
        return 0;
    k_members = filter(users(),is_khiraa);
    write("You pull on the rope, and a loud, eerie clang echos "+
    "throughout the halls!\n");
    say(QCTNAME(TP)+" pulls on the rope, and a loud, eerie clang "+
    "echos throughout the halls!\n");
    if(!sizeof(k_members))
    {
        write("You feel that your call was unheard.\n");
        return 1;
    }
    k_members->catch_msg("You hear the faint echo of the temple "+
    "bell ring, and a vison of "+QNAME(TP)+" enters your mind.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(ring_bell,"pull");
}
