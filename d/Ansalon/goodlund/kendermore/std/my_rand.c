int my_rand(int range)
{
    int t = time();
    t /= 2;
    t ^= random(255);
    t %= range;
    return(t);
}
