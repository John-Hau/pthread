#!/usr/bin/python3.7
import os
import tkinter as tk
#import tkinter 

os.environ['DISPLAY'] = ':0'

root = tk.Tk()
frame = tk.Frame(root)
frame.pack()
label = tk.Label(frame, text="Hey there.")
label.pack()
quitButton = tk.Button(frame, text="Quit", command=frame.quit)
quitButton.pack()
root.mainloop()
