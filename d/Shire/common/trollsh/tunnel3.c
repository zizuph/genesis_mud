#include "defs.h";
inherit "/d/Shire/common/trollsh/tunnrom";

create_tunnrom()
{
    set_short("dark tunnel");
    set_long(
        "You are walking in a dark and humid tunnel under the trollshaws. There "
        +"is a strong feeling of evil in here, you can almost touch it. The air "
        +"is varm and moisty, with a foul smell in it. The ground is wet and soft, "
    +"and scattered around lay pieces of bones, broken bones.\n");
    
    add_prop(ROOM_I_LIGHT,-1);
    add_item("ground" ,
        "The ground is very soft, but not so soft that you sink in it. It is mostly soil "
        +"but since is it so hard, you gather there must be some other things in it.\n"
           );
    
    add_item(({"tunnel"}),
        "The tunnel is dark and humid. It is about 4 meters high and only half as wide.\n"
    
    );
     
    add_exit(TROLLSH_DIR + "tunnel7", "northwest", 0, 2);
    add_exit(TROLLSH_DIR + "tunnel2", "south", 0, 2);    
}
