/* File: /d/Shire/common/trollsh/trollsh19.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "/d/Shire/common/defs.h"


#define MAX_WOLF 3

//Global variables.
object leader, *wolf = ({ });

//Prototypes
void make_wolf();

void reset_shawrom()
{
    make_wolf();
} 

create_shawrom()
{

    set_short("Northheast in the Trollshaw");
    set_extraline("Here someone must have fertilized the soil to the extreme. "
	+"The bushes have grown totally out of control and the trees are "
	+"very thick and sturdy. As you move about in this place you smell "
	+"a strange stench. But you are not quite "
	+"sure where to place it. But it makes your nose wrinkle a bit. "
	+"There is a ridge building up to the south and and a narrow path "
   +"going up to another ridge to the west. To the north there is another "
	+"path. ");

  
    add_exit(TROLLSH_DIR + "shaws16", "west", 0);
    add_exit(TROLLSH_DIR + "shaws18", "south", 0);
    add_exit(TROLLSH_DIR + "shaws20", "north", 0);
    add_exit(TROLLSH_DIR + "shaws21", "northwest", 0);

    reset_shawrom();    
}

void
make_wolf()
{
    int i;
    
    if(!leader)
    {
        leader = clone_object(TROLLSH_DIR + "npc/wolf_leader");
        leader->move(TO);
        tell_room(TO, CAP(LANG_ADDART(leader->query_nonmet_name()))+
        	" comes lurking trough the forest.\n");
    }
    if(!sizeof(wolf))
        wolf = allocate(MAX_WOLF);
    for(i = 0; i < MAX_WOLF; i++)
       if(!wolf[i])
       {
           wolf[i] = clone_object(TROLLSH_DIR + "npc/wolf");
           leader->team_join(wolf[i]);
           wolf[i]->move(TO);
           tell_room(TO, CAP(LANG_ADDART(wolf[i]->query_nonmet_name()))+
            	" suddenly jump out in view.\n");
       }
    else  
    if(wolf[i]->query_leader() !=leader)
        leader->team_join(wolf[i]);
}
