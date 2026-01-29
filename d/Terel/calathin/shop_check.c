#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
int enemy_check();
int race_invis_enemy();


int
race_invis_enemy()
{
    int chat;
    chat = random(5);

    if(!CAN_SEE_IN_ROOM(keeper) || !CAN_SEE(keeper, TP))
    {
        switch(chat)
        {
            case 0:
                keeper->command("say If you want to do business turn on "+
                              "the light.");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say I can't see what you want to sell.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's turned out the lights?");
                keeper->command("peer");
                break;
        }
        return 1;
    }
    if(TP->query_prop(OBJ_I_INVIS))
    {
        switch(chat)
        {
            case 0:
                keeper->command("peer");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say Damn rats.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's there?");
                keeper->command("peer");
                break;
        }
        return 1;
    }
    if(enemy_check())
    {
        switch(chat)
        {
            case 0:
                keeper->command("say You enter our home and slay us and now "+
                "you want us to do business with you?");
                break;
            case 1:
                keeper->command("say I refuse to do business with enemies of "+
                "out town!");
                break;
            case 2:
                keeper->command("say Get out! I want no business from you!");
                break;
            case 3:
                keeper->command("say You've got a lot of nerve, get out of "+
                "here!");
                break;
            case 4:
                keeper->command("say Leave now, or if the guards don't find "+
                "you I'll call them!");
                break;
        }
        return 1;
    }
} 


int
enemy_check()
{
    object kill_logger = find_object(KILL_LOGGER);
    if(kill_logger->query_killer(TP->query_name()))
    {
        return 1;
    }
    return 0;

}

