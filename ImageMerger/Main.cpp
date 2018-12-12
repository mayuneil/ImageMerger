#include <Siv3D.hpp>

double calcScale(double sizeX, double sizeY)
{
	double scaleX = 1.0;
	double scaleY = 1.0;
	const double maxWidth = 300;
	const double maxHeight = 150;
	if (maxWidth < sizeX)
	{
		scaleX = maxWidth/ sizeX;
	}
	if (maxHeight < sizeY)
	{
		scaleY = maxHeight / sizeY;
	}
	return Min(scaleX, scaleY);
}

void Main()
{
	Array<Texture> textures;
	Window::Resize(300, 300);
	while (System::Update())
	{
		if (textures.size() <= 3 && DragDrop::HasNewFilePaths())
		{
			const Array<DroppedFilePath> items =
				DragDrop::GetDroppedFilePaths();
			for (int i = 0; i < items.size(); ++i)
			{
				if (const Texture tmp{ items[i].path })
				{
					textures.push_back(tmp);
				}
			}
		}

		const int numOfTextures = textures.size();
		double sumOfheight = 0;
		int width = 0;
		int height = 0;
		double scale = 0;
		double maxwidth = 0;
		for (int a = 0; a < numOfTextures; a++)
		{
			width = textures[a].width();
			height = textures[a].height();
			scale = calcScale(width, height);
			textures[a].scaled(scale).draw(0, sumOfheight);
			if (maxwidth < scale*width) 
			{
				maxwidth = scale*width;
			}
			sumOfheight += scale*height;
		}
		if (Window::Height() < sumOfheight)
		{
			Window::Resize(maxwidth , sumOfheight);
		}


	}
}