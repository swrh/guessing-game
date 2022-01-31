# Guessing Game

This is a console guessing game that tries to guess which animal you're
thinking. It makes questions about it and if it doesn't guess it right, it
learns about it so you can ask again. You could think of it as a stupid
Akinator.

## Algorithm

It doesn't use any kind of artificial intelligence or external database to
guess or to store the animals "learned". It's nothing but a binary tree stored
in memory, and if the animal is not in the tree, it is stored.
