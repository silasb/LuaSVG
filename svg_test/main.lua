require 'LuaSVG'

function love.load()
  path1 = love.filesystem.read('path1.svg')
  --local svg_file = svg.load(abs_path('path1.svg'))

  svg_file = svg.eval(path1)
end

function abs_path(file)
  return(root_path() .. '/' .. file)
end

function root_path()
  return love.path.getfull(love.arg.options.game.arg[1])
end

function love.draw()
  love.graphics.print('SVG Test', 0, 0)

  --print(svg_file)

  --[[for i,path in pairs(svg_file) do
    --print(i,path)
    for j,v in pairs(path) do
      --print(j,vertex.x, vertex.ykkkkkkkkkk)
      love.graphics.point(v.x, v.y)
    end
  end]]

end

function dump(o)
  if type(o) == 'table' then
    local s = '{ '
    for k,v in pairs(o) do
      if type(k) ~= 'number' then k = '"'..k..'"' end
      s = s .. '['..k..'] = ' .. dump(v) .. ','
    end
    return s .. '} '
  else
    return tostring(o)
  end
end
