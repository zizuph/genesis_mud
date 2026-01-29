#define TOBACCO_DIR "/d/Shire/common/obj/"

/* To change the chances of a hobbit getting a certain type of tobacco,
 * you will have to #undefine all of these RANGE_'s, and then redefine
 * them.  Bigger numbers should be assigned to the types a particular hobbit
 * is more likely to have.  Poor hobbits, like my bandit, should have
 * only home_brew or bree, while someone like the rich innkeepers should
 * settle for nothing less than old_brandy.  However, I was too lazy to
 * do this, so all hobbits will get the same mix if no one else changes it.
 *
 * Astro!
 */
#define RANGE_FIRST  5
#define RANGE_SECOND RANGE_FIRST + 4
#define RANGE_THIRD  RANGE_SECOND + 3
#define RANGE_FOURTH RANGE_THIRD + 3
#define RANGE_FIFTH  RANGE_FOURTH + 3
#define RANGE_SIXTH  RANGE_FIFTH + 2

void clone_tobacco()
{
    int freq;

    freq = random(20);
    seteuid(getuid());
    if (freq < RANGE_FIRST)
        clone_object(TOBACCO_DIR + "tob_home_brew")->move(this_object());
    else if (freq < RANGE_SECOND)
        clone_object(TOBACCO_DIR + "tob_bree")->move(this_object());
    else if (freq < RANGE_THIRD)
        clone_object(TOBACCO_DIR + "tob_south")->move(this_object());
    else if (freq < RANGE_FOURTH)
        clone_object(TOBACCO_DIR + "tob_northeast")->move(this_object());
    else if (freq < RANGE_FIFTH)
        clone_object(TOBACCO_DIR + "tob_west")->move(this_object());
    else
        clone_object(TOBACCO_DIR + "tob_old_brandy")->move(this_object());
}
