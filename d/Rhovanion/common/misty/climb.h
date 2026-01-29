#define ROOM_U        "/d/Rhovanion/common/misty/r1.c"
#define ROOM_D        "/d/Rhovanion/common/misty/p18.c"
#define ROOM_CLIMB    "/d/Rhovanion/common/misty/climb.c"
#define DELAY         4  /* seconds delay between mesages */
#define DAMAGE        10 /* coefficient for damage */

#define START_UP_D    tell_room(ROOM_D,QCTNAME(TP)+" starts to climb down from the rock.\n")

#define START_UP_U    tell_room(ROOM_U,QCTNAME(TP)+" crawls to the edge and with a sad wave starts to climb down. Remember! You will have to go there too.\n")

#define START_UP      TP->catch_msg("You crawl to the edge and with a sad wave start to climb down.\n")

#define START_DOWN_D  tell_room(ROOM_D,QCTNAME(TP)+" starts to climb the rock.\n")

#define START_DOWN    TP->catch_msg("You start to climb the rock...\n")

#define HIGH_5        TP->catch_msg("You are a few feet above the ground.\n")

#define HIGH_10       TP->catch_msg("You are steadily moving further.\n")

#define HIGH_15       TP->catch_msg("You have reached the middle of the rock.\n")

#define HIGH_20       TP->catch_msg("You have found a crack and rest a bit before the next part.\n")

#define HIGH_25       TP->catch_msg("You are only little below the top.\n")

#define HIGH_5_D    tell_room(ROOM_D, QCTNAME(TP)+" is a few feet above the ground.\n")

#define HIGH_10_D     tell_room(ROOM_D,QCTNAME(TP)+" is steadily moving further.\n")

#define HIGH_15_D     tell_room(ROOM_D,QCTNAME(TP)+" has reached the middle of the rock.\n")

#define HIGH_20_D     tell_room(ROOM_D,QCTNAME(TP)+" has found a crack and "+HE(TP)+" is resting a bit before the next part.\n")

#define HIGH_25_D     tell_room(ROOM_D,QCTNAME(TP)+" is only little below the top.\n")

#define END_UP        TP->catch_msg("You crawl through the edge of the rock...\nYou made it!!!.\n")

#define END_UP_D    tell_room(ROOM_D,QCTNAME(TP)+" made it!!!\n")

#define END_UP_U    tell_room(ROOM_U,QCTNAME(TP)+" comes crawling through the edge of the rock.\n")

#define END_DOWN      TP->catch_msg("You jump down the last few inches.\nWhat a relief that you are down again!\n")

#define END_DOWN_D      tell_room(ROOM_D,QCTNAME(TP)+" jumps down the last few inches.\n"+QCTNAME(TP)+" made it!!!\n")

#define FALL_DOWN_W   TP->catch_msg("Oooops..!!! You lost your grip and slipped down.\nYou shout: AAAAAAAaaaaaaaaa.....\nOouch, it hurts!\nFortunately you wanted to go down anyway...\n")

#define FALL_DOWN_U   TP->catch_msg("Oooops..!!! You lost your grip and slipped down.\nYou shout: AAAAAAAaaaaaaaaa.....\nOouch, it hurts!\nNow you have to try it again...\n")

#define FALL_DOWN_D tell_room(ROOM_D,QCTNAME(TP)+" lost the grip on the rock and fell down.\n")

#define SHOUT_D_W    tell_room(ROOM_D,QCTNAME(TP)+" shouts: AAAAAAAaaaaaaaaa..... \nWell, "+TP->query_pronoun()+" wanted to go down anyway...\n")

#define SHOUT_D_U    tell_room(ROOM_D,QCTNAME(TP)+" shouts: AAAAAAAaaaaaaaaa..... \nNow "+TP->query_pronoun()+" has to try again...\n")

#define SHOUT_U       if(TP->query_gender()){ tell_room(ROOM_U,"A female "+TP->query_race_name()+" voice shouts: AAAAAAAaaaaaaaaa.....\n");} else{ tell_room(ROOM_U,"A male "+TP->query_race_name()+" voice shouts: AAAAAAAaaaaaaaaa.....\n");}


