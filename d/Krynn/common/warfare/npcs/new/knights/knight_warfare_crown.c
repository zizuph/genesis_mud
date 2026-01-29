
/* 
 * A knight of the Crown of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/knight_base";

int level;
int sublevel = 4; // Crown knight

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 0; // 20% 'gallant' (139 stat average)
        break;
        case 2..6:
            level = 1; // 50% 'experienced' (169 stat average) 
        break;
        default:
            level = 2; // 30% 'veteran' (189 stat average)
        break;
    }

    return level;
}

public void
create_knight_soldier()
{
    set_knight_level(random_soldier_type(), sublevel, "crown");
}
 