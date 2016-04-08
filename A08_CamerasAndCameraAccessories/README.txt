Justin John
Lauren-Alexandra Stapleford

I was having some trouble where the program was throwing an error on the Render() calls, but I don't know if that will be an issue for you.

We have all the getters and setters set up and working. We orignally were overthinking it and made it more complicated than it should have been, but it's good now.
The Move methods work perfectly, and are bound properly: W = forward, S = back, A = left, D = right, Q = up, E = down.

We had a lot of trouble with quaternions, but at our final hour, we figured it out. We bound the pitch and yaw to the mouse, if you click and hold right mouse. ChangeRoll
is bound to R and T, rolling to the left and right respectively.