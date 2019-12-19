/**
 * @file vor.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//included within  "vor.h" for template instantiation
 
 
/* vorDotDFS given as an example for PA2 */
animation filler::vorDotDFS(PNG& img, double density,
                                int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid,dotSize);
    return vor<Stack>(img, density, a, frameFreq);
}
 
animation filler::vorSolidDFS(PNG& img, double density, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    solidColorPicker s;
    return vor<Stack>(img, density, s, frameFreq);
}
 
animation filler::vorFadeDFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    fadeColorPicker f(fadeFactor);
    return vor<Stack>(img, density, f, frameFreq);
}
 
 
/* vorDotBFS given as an example for PA2 */
animation filler::vorDotBFS(PNG& img, double density,
                                int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid, dotSize);
    return vor<Queue>(img, density, a, frameFreq);
}
 
animation filler::vorSolidBFS(PNG& img, double density, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    solidColorPicker s;
    return vor<Queue>(img, density, s, frameFreq);
}
 
animation filler::vorFadeBFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    fadeColorPicker f(fadeFactor);
    return vor<Queue>(img, density, f, frameFreq);
}
 
int filler::checkFraming(PNG& img, int processedPixels, animation& anim, int frameFreq){
    if((processedPixels % frameFreq == 0)){
        anim.addFrame(img); //for every frameFreq pixels filled, add a frame
        processedPixels = 0; //to prevent int overflow!    
    }
    return processedPixels;
}
 
int filler::processCenter(center c, PNG& img, OrderingStructure<point>& os, vector<vector<bool>>& processed, colorPicker& fillColor, int processedPixels, animation& anim, int frameFreq){
    if(processed[c.x][c.y] == false){
        *(img.getPixel(c.x, c.y)) = fillColor(point(c)); 
        processed[c.x][c.y] = true;  
        processedPixels++;
        processedPixels = checkFraming(img, processedPixels, anim, frameFreq);
    }
    return processedPixels;
}

bool filler::checkNeighbor(int level, PNG& img, point p, vector<vector<bool>>& processed){
    center c = p.c;
    if(p.x >= img.width() || p.y >= img.height()){
        return false;
    }
    if(processed[p.x][p.y] == true){
        return false;
    }
    double distance = sqrt((p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y));
    if(distance > level+1){
        return false; //a valid neighbour's distance can be AT MOST level+1 for the current level "level"!!!
    } //we ensure that all points with distances <=level are processed before any point with distance >level!
    return true;
}
 
int filler::processNeighbor(int level, OrderingStructure<point>& os, PNG& img, point p, vector<vector<bool>>& processed, colorPicker& fillColor, int processedPixels, animation& anim, int frameFreq){
    bool valid = checkNeighbor(level, img, p, processed); //check if the neighbour is valid - see checkNeighbour
    if(valid == true){
        os.add(p);
        *(img.getPixel(p.x, p.y)) = fillColor(p);
        processed[p.x][p.y] = true;
        processedPixels++;
        processedPixels = checkFraming(img, processedPixels, anim, frameFreq);
    }
    return processedPixels;
}
 
int filler::processLevel(PNG& img, OrderingStructure<point>& os, vector<vector<bool>>& processed, colorPicker& fillColor, int processedPixels, animation& anim, int frameFreq){
    if(!os.isEmpty()){
        point p = os.peek(); //remove 1st and then check the next one in the loop
        center c = p.c;
        int level = p.level; //get the current level (= level of the point which is at the head of the os - stack or queue)
        int newPixels;
        while(p.level <= level){ //while there is a point with the same level
            p = os.remove();
            if(os.isEmpty()){ //point has no neighbours
                return processedPixels;
            }
            //find p's unprocessed neighbours, add them to the os, color them, mark them as processed
            //put neighboring pixels **ONTO** the queue or stack as: UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y), DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)
            newPixels = processNeighbor(level, os, img, point(p.x, p.y-1, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x-1, p.y-1, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x-1, p.y, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x-1, p.y+1, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x, p.y+1, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x+1, p.y+1, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x+1, p.y, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            newPixels = processNeighbor(level, os, img, point(p.x+1, p.y-1, c, level+1), processed, fillColor, processedPixels, anim, frameFreq);
            processedPixels = newPixels;
            p = os.peek();
        }
        return processedPixels;
    } else {
        return -1;
    } 
}
 
 
 
template <template <class T> class OrderingStructure>
animation filler::vor(PNG& img, double density, colorPicker& fillColor,
                       int frameFreq)
{
 
    /**
     * @todo You need to implement this function!
     *
     * This is a general description of a space filling algorithm, where 
     * the space is partitioned into a set of regions each color of which
     * is determined by the color of a point 
     * chosen from an original image. We call those original points
     * "centers." (See pictures in the specification.)
     *
     * The algorithm requires ordering structures used to orchestrate
     * the sequence of points filled. This structure type info is passed to the 
     * fill algorithm via its template parameter. For a breadth-first fill,
     * we use Queues, and for a depth-first fill, we use Stacks. Function
     * vorDotDFS provides an example call to function vor.
     * 
     * The algorithm includes the following steps:
     * 1) you will first select a random set
     * of coordinates (and their colors) to use as centers from which to
     * begin the fill. (this function is in file vor_given.cpp -- for 
     * testing purposes, you'll use regularly spaced points, rather than 
     * random.)
     * 2) Initialize a structure to use to maintain a collection of 
     * ordering structures
     *
     * 3) Initialize the fill: For each center c, in round-robin order, 
     *     do the following:
     *     a)  add the center to the its ordering structure. (every center 
     *         its own!
     *     b)  mark the location of that center as processed (the way you 
     *         do this is up to you!)
     *     c)  we have a choice to actually set the color of the pixel in 
     *         the fill when we add or when we remove. In our test cases, 
     *         we assume that you will change a color when a point is 
     *         added to a structure. (this is mostly relevant for checking 
     *         the animations.)
     *
     * 5) Complete the fill: Until all ordering structures (OS) are empty, 
     *    do the following for each OS, in a round robin order, indexing
     *    the iterations by k (an integer distance from the center):
     *    
     *      For each point less than or equal to distance k from its center:
     *      a)Remove the  point p from the ordering structure, and then...
     *
     *        i.    add p's unprocessed neighbors to the ordering structure if 
     *              they are within the appropriate distance from the center. We 
     *              describe this more carefully below. We call these the "valid"
     *              neighbors.
     *        ii.    use the colorPicker to set the new color of the valid neighbors.
     *        iii.    mark the valid neighbors as processed.
     *        iv.    as each neighbor is processed, if it is an appropriate 
     *              frame, send the current PNG to the
     *              animation (as described below).
    *
     *      b) When implementing your breadth-first and depth-first fills, 
     *            you will need to explore neighboring pixels in some order.
     *
     *        For this assignment, each pixel p has *up to* 8 neighbors, consisting of 
     *        the 8 pixels who share an edge with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y), 
     *        DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        TWO IMPORTANT NOTES: 
     *        1) *UP* here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *        2) not all of the 8 neighbors will be processed at every iteration of the
     *        while loop. You must assure that all vertices distance k or less
     *        from the center are processed (colored and put on the queue) before
     *        ANY whose distance is *greater than* k. k is a non-negative integer. 
     *        Finally, distance is the standard Euclidean distance  (computed 
     *        using the Pythagorean theorem). It is this requirement that assures
     *        that the fill grows outward from the center in the shape of a circle,
     *        rather than a diamond or a square. 
     *
     *      c) For every g pixels filled, **starting at the gth pixel**, you
     *        must add a frame to the animation, where g = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *      d) Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */
 
 
     /* Your code here. As a point of reference, we used three different helper
      * functions to complete this code. You may add as many as you wish, since
      * we will be grading vor.h. File "vor_given.cpp also includes the function
      * used to generate the original set of centers. 
      */
    animation anim;
    int processedPixels = 0; //used for adding a frame to the animation for every given number of pixels processed
    vector<center> centers = randSample(img, density); //select a random set of coordinates as centers to begin the fill from
    Queue<OrderingStructure<point>> structures; //queue of ordering structures; queue of queues/stacks holding centers and their neighbouring coordinates
    vector<vector<bool>> processed(img.height(), vector<bool> (img.width(), false)); //initially, no coordinates are processed

    for(int i=0; i<centers.size(); i++){
        OrderingStructure<point> os;
        os.add(point(centers[i])); //add each center to its own ordering structure
        int newPixels = processCenter(centers[i], img, os, processed, fillColor, processedPixels, anim, frameFreq);
        processedPixels = newPixels;
        structures.add(os); //add the current os to the queue of os's  
    }
    
    //while there are still non-empty ordering structures in the queue
    while(!structures.isEmpty()){
        OrderingStructure<point> currentOS = structures.peek(); //do this for each os:
        if(currentOS.isEmpty()){
            structures.remove(); //simply remove if emptied
        } else {
            currentOS = structures.remove(); //temporarily remove the os to process the given level of coordinates for that os
            int newPixels = processLevel(img, currentOS, processed, fillColor, processedPixels, anim, frameFreq); //process a level for that os
            processedPixels = newPixels;
            if(!currentOS.isEmpty()){
                structures.add(currentOS); //add back if not emptied; there are more "level"s to process
            }
        }
    }
    
    anim.addFrame(img); //one last frame
    return anim;    
}