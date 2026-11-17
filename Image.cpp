//
//  image.cpp
//  
//
//  Created by Zach on 9/2/26.
//

#include "Image.h"
//The default constructor. A default Image has 0 height and 0 width. The data vector should be resized to fit the width and height.
Image::Image( )
{
    m_height=0;
    m_width=0;
    
    m_image_data.resize(0);
}
// A constructor with parameters for the height and width. The data members should be set according to theparameters. The data vector should be resized to fit the width and height.
Image::Image( const int& height, const int& width )
{
    m_height = height;
    m_width = width;
    
    m_image_data.resize(height*width*NUM_CHANNELS);
}

//Returns the height of the Image.
int Image::getHeight( ) const
{
    return m_height;
}
//Returns the width of the Image.
int Image::getWidth( ) const{
    return m_width;
}
//Checks if row, column, and channel are all within the legal limits. Returns true if they all are, and false otherwise.
bool Image::indexValid( const int& row, const int& column, const int& channel ) const
{
    if(row<0 || row >= m_height)
        return false;
    if(column<0 || column >= m_width)
        return false;
    if(channel < 0 || channel >= NUM_CHANNELS)
        return false;
    
    return true;
}

int Image::index( const int& row, const int& column, const int& channel ) const {
    int location;
    
    location = (row * m_width * NUM_CHANNELS) 
	    + (column * NUM_CHANNELS) 
	    + channel;
    
    return location;
    
}



int Image::getChannel( const int& row, const int& column, const int& channel ) const{
    if(!indexValid(row,column,channel))
        return -1;
    int location = index(row,column,channel);
    
    return m_image_data[location];
}

void Image::setHeight( const int& height ) {
    if(height < 0)
        return;
    
    m_height = height;
    
    m_image_data.resize(m_width * m_height * NUM_CHANNELS);
}
void Image::setWidth( const int& width ){
    if(width < 0)
        return;
    
    m_width = width;
    
    m_image_data.resize(m_width * m_height * NUM_CHANNELS);
}
void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if( !indexValid(row, column, channel))
        return;
    int location = index(row, column, channel);
    m_image_data[location] = value;
    
}
