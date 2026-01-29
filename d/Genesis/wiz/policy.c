#pragma save_binary

#include "default.h"

void
create_room() 
{
    set_short("Administration Policy room");
    set_long("The board in this room is used by the administration of " +
	"the game to write its policy regarding certain matters. The " +
	"board is not meant for discussion and the notes should not " +
	"contradict with eachother. In case they do, the latest note " +
	"on the topic is valid.\n");

    add_default_exits();

    setuid();
    seteuid(getuid());
    clone_object(THIS_DIR + "policy_board")->move(this_object());
}
