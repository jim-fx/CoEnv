<script lang="ts">
	import { fade } from 'svelte/transition';
	import { quartInOut } from 'svelte/easing';
	import { humaneNumbers } from '$lib/helpers';

	export const startYear = 2005;
	export let prognoseAfterIndex = Infinity;
	export let data: number[] | { data: number; date: string }[] = [];

	function scaleY(node: SVGElement | HTMLElement, { duration = 100, delay }) {
		return {
			delay,
			duration,
			css: (t: number) => `transform-origin: 0 100%; transform: scaleY(${quartInOut(t)}); `
		};
	}

	$: amount = data.length;
	$: filter = Math.floor(amount / 10);
	$: max = Math.max(...data.map((d) => (typeof d === 'number' ? d : d['data'])));
	$: dp = data.map((v, i) => {
		const isNumber = typeof v === 'number';
		const value = isNumber ? v : v['data'];
		let date = isNumber ? 2005 + i : v['date'];

		if (typeof date === 'string') {
			date = date.split('-')[0];
		}

		return {
			height: (value * 100) / max,
			date: i % filter === 0 ? date : '',
			x: (100 / amount) * i
		};
	});
	$: console.log(max);
</script>

<div center out:fade>
	<svg viewBox="0 0 100 100">
		{#each Array(10) as _, i}
			<text in:fade x="101" y={100 - i * (100 / 9)} style="text-anchor: start;">
				– {humaneNumbers(Math.floor((i / 9) * max))}
			</text>
		{/each}

		{#each dp as { x, height, date }, i}
			<rect
				class:prognose={i > prognoseAfterIndex}
				in:scaleY={{ delay: (i * 2000) / amount, duration: 300 }}
				{x}
				y={100 - height}
				width={100 / amount}
				{height}
			/>
			{#if date}
				<text in:fade x={x + 100 / amount / 2} y={102}>{date}</text>
			{/if}
		{/each}
	</svg>
</div>

<style>
	svg {
		height: 80vh;
		width: 80vw;
		overflow: visible;
	}
	rect {
		fill: white;
	}

	rect.prognose {
		fill: rgba(255, 255, 255, 0.5) !important;
		stroke: white;
		stroke-alignment: inner;
		transform: scale(0.998);
		stroke-width: 0.5px;
	}

	text {
		text-anchor: middle;
		font-size: 2px;
		fill: white;
	}
</style>
