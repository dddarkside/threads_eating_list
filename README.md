Hi, this is my first project on GitLab, please do not be strict)

Sorry for maybe some kind of unreadeble code

For your comfort, I made makefile:

> all      - just making executable file nammed thr_eat_list
> DEFAULT  - same as "all" + run executable file with argument 100000
> DEBUG    - making executable file with checking data races and argument 100000

if you gonna run executable manually, you shoud use argument like 100000 or more, because list of small size will be processed by one thread faster than th second one will start work

Also I pinned executable file if you need it for some reasons

Have a good day!
