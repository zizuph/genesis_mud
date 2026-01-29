
/* 
 * A Qualinesti elf magus of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_qualinesti";

int level;
int sublevel = 4; // magus

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..3:
            level = 1; // 40% 'experienced' (125 stat average) 
        break;
        default:
            level = 2; // 60% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_elf_soldier()
{
    set_elf_level(random_soldier_type(), sublevel, "qualinesti");
}
 