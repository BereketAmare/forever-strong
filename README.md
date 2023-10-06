# Blinking Game - README

[Video Walkthrough](https://youtu.be/jpW6JRsOm9M?t=345)

## Table of Contents
1. [Overview](#overview)
2. [Product Spec](#product-spec)
3. [Dependencies](#dependencies)
4. [How to Use](#how-to-use)
5. [Contributors](#contributors)
6. [Final Product](#final-product)
7. [Video Walkthrough](#video-walkthrough)

## Overview
### Description
The Blinking Game is an interactive computer vision-based game where the goal is to avoid blinking for as long as possible. The program captures video feed from the user's webcam and detects blinks using the dlib library. When the user blinks, the game stops, and the time taken is displayed.

### App Evaluation
- **Category:** Game / Computer Vision
- **Mobile:** This is a desktop application but could be adapted for mobile use.
- **Story:** Tests users' ability to resist blinking and compete for the longest time.
- **Market:** All ages.
- **Habit:** Users can play the game whenever they feel like challenging themselves.
- **Scope:** Could expand to include multiple players, leaderboard system, etc.

## Product Spec

- User sees live video feed of themselves.
- User's blinking is detected accurately.
- Time is displayed, indicating how long the user resisted blinking.
  
#### Optional Nice-to-have 
- Leaderboard system to rank users.
- Multiplayer mode where users compete in real-time.
- Personal statistics tracking for individual users.

### Screen Archetypes
- **Main Screen**
  - User sees live video feed.
  - Time counter is displayed.
  - Option to restart or exit the game.

### Flow Navigation (Screen to Screen)
- **Main Screen** -> Game starts -> User blinks -> Game stops -> Display time -> Option to restart or exit.

## Dependencies
- OpenCV (for video capture and processing)
- dlib (for face and eye detection)

## How to Use
1. Ensure you have OpenCV and dlib libraries installed.
2. Clone the repository.
3. Run the program.
4. The webcam will activate, and the game will start. Try not to blink!
5. When you blink, the time taken will be displayed along with options to restart or exit.

## Contributors
- Tibebu Getachew
- Bereket Amare
- Kidus Mekonnen
