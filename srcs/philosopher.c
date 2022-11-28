#include "philosopher.h"

int main(int ac, char **av)
{
    t_data  s_data;

    if (exit_if_args_errors(ac, av) == ERROR)
        return (1);
    if (init_struct(&s_data, ac, av) == ERROR)
        return (1);
}