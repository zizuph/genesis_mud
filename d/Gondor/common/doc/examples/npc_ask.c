/*
 * /d/Gondor/common/doc/examples/npc_ask.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * an example of using the new add_ask_item() routine in
 * ~gondor/std/monster.c
 */

#pragma strict_types

inherit "/d/Gondor/std/monster";

#include <const.h>
#include "/d/Gondor/defs.h"

public void	create_gondor_monster();


/*
 * Function name:	create_gondor_monster
 * Descrption	:	set up npc with test questions
 */
public void
create_gondor_monster()
{
    set_name("npc");
    set_short("test npc");
    set_long("A helpful test npc. Ask her 'question1', 'question2', ... " +
	"'question5'.\n");
    set_gender(G_FEMALE);

    /* a question with 3 different answers, each answer having a
     * single part
     */
    add_ask_item( ({ "question1", "question 1", "1", "one" }),
	({ "say This is the first answer to question one.",
	   "say This is the second answer to question one.",
	   "say This is the third answer to question one.",
	}) );

    /* 1 answer that has 3 parts, including soul command directed
     * at the player
     */
    add_ask_item( ({ "question2", "question 2", "2", "two" }),
	({ ({ "grin cheer",
	      "say I am now answering question two.",
	      "wink sig @@query_player@@",
	   }),
	}) );

    /* an answer using emote */
    add_ask_item( ({ "question3", "question 3", "3", "three" }),
	"emote thinks hard about the answer to question three.");


    /* the 2nd answer echos a message to the room */
    add_ask_item( ({ "question4", "question 4", "4", "four" }),
   	({
	   "eyebrow @@query_player@@",
   	   ({ "emote gestures mysteriously.", 
   	      "@@echo_to_room|There is a distant mutter of thunder, " +
   		  "and the air grows chill and heavy.@@", 
	      "grin wick",
   	   }),
	}),
    );

    /* set up three default answers; the 1st and 2nd answers
     * each have two parts. the 3rd answer has only one, but
     * that in that one, she addresses the player by name
     */
    set_default_answer(
	({
	   ({ "shrug", "say How should I know?", }),
	   ({ "say I have not the faintest idea.", "smile sweetly", }),
	   "say You ask such silly questions, @@query_player_name@@.",
	})
    );
} /* create_gondor_monster */
