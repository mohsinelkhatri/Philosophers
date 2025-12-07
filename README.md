<h1 align="center">🍝 Philosophers – Multithreading Project (42 / 1337 School)</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/POSIX-pthreads-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Mandatory%20Only-orange?style=for-the-badge">
</p>

<p style="font-size:16px;">
The <strong>Philosophers</strong> project explores threading, synchronization, race conditions, and deadlock management.  
You must simulate philosophers eating, thinking, and sleeping while sharing forks using <strong>mutexes</strong>.  
This README covers the project <strong>without bonus</strong>.
</p>

<hr>

<h2 align="center">📌 Project Overview (Mandatory Part)</h2>

<p>You must simulate the famous “Dining Philosophers Problem” using:</p>

<ul>
  <li>Threads to represent philosophers</li>
  <li>Mutexes for forks & printing</li>
  <li>Accurate time management</li>
  <li>A monitoring system to detect death</li>
  <li>A clean shutdown of all threads and resources</li>
</ul>

<p>Each philosopher alternates between:</p>

<ul>
  <li>🍽 Eating</li>
  <li>💭 Thinking</li>
  <li>😴 Sleeping</li>
</ul>

<p>The simulation stops when:</p>

<ul>
  <li>❌ A philosopher dies (did not eat in time)</li>
  <li>✅ All philosophers have eaten the required number of meals (if provided)</li>
</ul>

<hr>

<h2 align="center">📁 Repository Structure (Your Project)</h2>

<pre style="background:#1e1e1e; color:#00e676; padding:15px; border-radius:8px;">
philo/
│
├── actions.c
├── cleanup.c
├── ft_putstr_fd.c
├── forks.c
├── init_sim.c
├── main.c
├── monitor.c
├── parse_args.c
├── philo.h
├── print.c
├── room.c
├── routine.c
├── start_threads.c
├── time.c
└── utils_num.c
</pre>

<hr>

<h2 align="center">🧠 How the Simulation Works</h2>

<h3>1️⃣ Input Arguments</h3>

<p>Execution format:</p>

<pre style="background:#1e1e1e; color:white; padding:12px; border-radius:8px;">
./philo number_of_philos time_to_die time_to_eat time_to_sleep [meals_required]
</pre>

<ul>
  <li><strong>number_of_philos</strong> → number of threads</li>
  <li><strong>time_to_die</strong> → max ms before death</li>
  <li><strong>time_to_eat</strong></li>
  <li><strong>time_to_sleep</strong></li>
  <li><strong>meals_required</strong> (optional) → end simulation early</li>
</ul>

<p>Argument validation occurs in <strong>parse_args.c</strong>.</p>

<hr>

<h2 align="center">🔧 Explanation of Each File</h2>

<h3>📥 parse_args.c</h3>
<p>Validates user input and initializes simulation parameters.</p>

<h3>🏗 init_sim.c</h3>
<p>Allocates memory, initializes philosophers, mutexes, and shared structures.</p>

<h3>🍴 forks.c</h3>
<p>Creates and manages fork mutexes (one per philosopher).</p>

<h3>🔁 routine.c</h3>
<p>The core thread routine executed by each philosopher:</p>
<ul>
  <li>Pick forks</li>
  <li>Eat</li>
  <li>Sleep</li>
  <li>Think</li>
</ul>

<h3>📝 actions.c</h3>
<p>Implements atomic actions such as taking forks, eating, sleeping, thinking.</p>

<h3>🖨 print.c</h3>
<p>Thread-safe printing using a mutex. Prevents message overlap.</p>

<h3>⏱ time.c</h3>
<p>Handles timestamps, time differences, and custom usleep for accuracy.</p>

<h3>🕵️ monitor.c</h3>
<p>
A separate monitoring loop that:
<ul>
  <li>Detects when a philosopher has died</li>
  <li>Checks if everyone has eaten enough</li>
  <li>Triggers shutdown</li>
</ul>
</p>

<h3>🚪 cleanup.c</h3>
<p>Destroys mutexes and frees allocated memory.</p>

<h3>👥 start_threads.c</h3>
<p>Creates philosopher threads and starts the simulation.</p>

<h3>🏠 room.c</h3>
<p>Manages shared state of the simulation (forks, timing, running flags).</p>

<h3>🔢 utils_num.c</h3>
<p>Utility functions for safe integer parsing and numeric checks.</p>

<h3>✏️ ft_putstr_fd.c</h3>
<p>A custom helper to print string messages.</p>

<h3>🧠 philo.h</h3>
<p>All structures, typedefs, includes, and function prototypes.</p>

<hr>

<h2 align="center">🏃 Simulation Rules</h2>

<ul>
  <li>Every philosopher must eat with two forks.</li>
  <li>Mutexes prevent fork conflicts.</li>
  <li>The simulation must avoid deadlocks.</li>
  <li>Time must be accurate to avoid false deaths.</li>
  <li>Philosophers must drop forks after eating.</li>
</ul>

<p>You typically avoid deadlock via:</p>

<ul>
  <li>Odd/even fork picking order</li>
  <li>Small startup delays</li>
</ul>

<hr>

<h2 align="center">🧵 Threads & Mutexes</h2>

<p>The mandatory part uses:</p>

<ul>
  <li><strong>pthread_create</strong></li>
  <li><strong>pthread_join</strong></li>
  <li><strong>pthread_mutex_lock</strong></li>
  <li><strong>pthread_mutex_unlock</strong></li>
</ul>

<p>Each philosopher is one thread.  
Each fork is one mutex.</p>

<hr>

<h2 align="center">⏳ Time Management</h2>

<p>All timings use milliseconds.  
Accurate scheduling is done using:</p>

<ul>
  <li>Timestamp at program start</li>
  <li>Custom sleep function in <strong>time.c</strong></li>
  <li>Elapsed time checked continuously</li>
</ul>

<hr>

<h2 align="center">🛠 Compilation & Execution</h2>

<pre style="background:#1e1e1e; color:white; padding:12px; border-radius:8px;">
make
./philo 5 800 200 200
./philo 5 800 200 200 5
</pre>

<hr>

<h2 align="center">❗ Program Stops When:</h2>

<ul>
  <li>A philosopher dies → simulation ends immediately</li>
  <li>All philosophers ate enough meals (if argument provided)</li>
</ul>

<hr>

<h2 align="center">📚 Learning Outcomes</h2>

<ul>
  <li>Understanding concurrency & race conditions</li>
  <li>Thread synchronization with mutexes</li>
  <li>Detecting starvation & deadlock</li>
  <li>Accurate timing & stable loops</li>
  <li>Clean multithreaded architecture</li>
</ul>

<hr>

<h2 align="center">📜 License</h2>

<p style="font-size:16px;">
This README is created for students of <strong>42 Network / 1337 School</strong>.  
You may reuse, modify, or adapt it for your philo project.
</p>

<hr>

<h1 align="center">🍽 Good luck — and may none of your philosophers die! 🕰</h1>
