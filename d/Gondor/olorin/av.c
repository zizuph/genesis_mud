#pragma strict_types

public int
read_it(string filename)
{
    int     n,
            stat,
            sum;
    string *arr,
            foo;

    filename = "/d/Gondor/olorin/" + filename;
    if (file_size(filename) < 1)
    {
	write("No such file: " + filename + "\n");
	return -1;
    }

    arr = explode(read_file(filename), "\n");

    n = sizeof(arr);
    while (n-- > 0)
    {
	sscanf(arr[n], "%s(%d)%s", foo, stat, foo);
//	write("Line " + n + ": stat = " + stat + ".\n");
	if (stat > 0)
	    sum += stat;
	else
	    write("Error reading line " + n + ":\n" +
		  arr[n] + "\n" + 
		  "stat = " + stat + ".\n");
    }
    write("Sum = " + sum + "; n = " + (n = sizeof(arr)) + ".\n");
    return (sum * 100 / sizeof(arr));
}
