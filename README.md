# cinema-service

# INSTRUCTIONS
• Provide a cross-platform working solution with instructions on how to compile and run in a README.md file.
• Manage your time as best as possible in order to provide a working, well-written, well-tested application by the given dateline. If you are time-limited, better compromise on the delivered functionality rather than on code quality, documentation or testing.

# TASK
The main objective of this project is to provide the implementation of a backend service in C++ which is used by some other services (CLI or other User Interface) for booking online movie tickets. Booking a ticket means just blocking the required number of particular seats.
The end-user shall be able perform the following actions through the UI:
• View all playing movies
• Select a movie
• See all theaters showing the movie
• Select a theater
• See available seats (e.g., a1, a2, a3) for the selected theater & movie.
You can assume that all theaters have 20 seats capacity
• Book one or more of the available seats. Service should be able to handle
multiple requests simultaneously (no over-bookings)
# EXPECTATIONS
• You are allowed to use third-party libraries (Boost etc)
• Do not use any kind of DBMS (MySQL, PostgreSQL etc), storing in memory is ok.
• Clean, well-documented source code
• Unit test coverage
• Good to have source code in C++11 or later
• Documented APIs (header files) for the consumer
• The backend service can be a standalone process or embedded in a CLI
for the purpose of this test
• (Bonus) Conan package management
• (Bonus) Docker support
• (Bonus) Documentation generator (Doxygen etc)
# REFLECTION
• What aspect of this exercise did you find the most interesting?
• What did you find most cumbersome?
# Compile
cmake -S ./ -B Build && cmake --build Build -- -j 12