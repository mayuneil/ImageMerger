#include <Siv3D.hpp>

double calcScale(double sizeX, double sizeY)
{
	double scaleX = 1.0;
	double scaleY = 1.0;
	const double maxWidth = 1280;
	const double maxHeight = 720;
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
	Window::Resize(500, 500);
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
		if (numOfTextures == 1)
		{
			const int width = textures[0].width();
			const int height = textures[0].height();
			const double scale = calcScale(width, height);
			textures[0].scaled(scale).draw();
			Window::Resize(width * scale, height * scale);
		} 
		else if (numOfTextures == 2)
		{
			const int width = textures[0].width() + textures[1].width();
			const int height = textures[0].height();
			const double scale = calcScale(width, height);
			const Vec2 center = scale * Vec2(textures[0].width(), Max(textures[0].height(), textures[1].height()));
			textures[0].scaled(scale).drawAt(center.movedBy(-textures[0].width()*scale / 2, -textures[1].height()*scale / 2));
			textures[1].scaled(scale).drawAt(center.movedBy(textures[1].width()*scale/2, -textures[1].height()*scale / 2));
			Window::Resize(width * scale, height * scale);
		}
		else if (numOfTextures == 3)
		{
			const int width = Max(textures[0].width() + textures[1].width(), textures[2].width());
			const int height = textures[0].height() + textures[2].height();
			const double scale = calcScale(width, height);
			const Vec2 center = scale * Vec2(Max(textures[0].width(), textures[2].width()), Max(textures[0].height(), textures[1].height()));
			textures[0].scaled(scale).draw();
			textures[1].scaled(scale).drawAt(center.movedBy(textures[1].width()*scale / 2, -textures[1].height()*scale / 2));
			textures[2].scaled(scale).drawAt(center.movedBy(-textures[2].width()*scale / 2, textures[2].height()*scale / 2));
			Window::Resize(width * scale, height * scale);
		}
		else if (numOfTextures == 4)
		{
			const int width = Max(textures[0].width() + textures[1].width(), 
				textures[2].width() + textures[3].width());
			const int height = Max(textures[0].height() + textures[2].height(),
				textures[1].height() + textures[3].height());
			const double scale = calcScale(width, height);
			const Vec2 center = scale * Vec2(Max(textures[0].width(), textures[2].width()), Max(textures[0].height(), textures[1].height()));
			textures[0].scaled(scale).draw();
			textures[1].scaled(scale).drawAt(center.movedBy(textures[1].width()*scale / 2, -textures[1].height()*scale / 2));
			textures[2].scaled(scale).drawAt(center.movedBy(-textures[2].width()*scale / 2, textures[2].height()*scale / 2));
			textures[3].scaled(scale).drawAt(center.movedBy(textures[3].width()*scale / 2, textures[3].height()*scale / 2));
			Window::Resize(width * scale, height * scale);
		}
	}
}
